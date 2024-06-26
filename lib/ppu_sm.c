#include <ppu_sm.h>
#include <ppu.h>
#include <lcd.h>
#include <cpu.h>
#include <string.h>
#include <interrupts.h>

void pipeline_fifo_reset();
void pipeline_process();

void increment_ly()
{
    lcd_get_context()->ly++;
    
    if (lcd_get_context()->ly == lcd_get_context()->ly_compare)
    {
        LCDS_LYC_SET(1);

        if (LCDS_STAT_INIT(SS_LYC))
        {
            cpu_request_interrupt(IT_LCD_STAT);
        }
    }
    else
    {
        LCDS_LYC_SET(0);
    }
}


void load_line_sprites()
{
    int cur_y = lcd_get_context()->ly;

    u8 sprite_height = LCDC_OBJ_HEIGHT;
    memset(ppu_get_context()->line_entry_array, 0, sizeof(ppu_get_context()->line_entry_array));

    for (int i = 0; i < 40; i++)
    {
        oam_entry e = ppu_get_context()->oam_ram[i];

        // x = 0 means not visible...
        if (!e.x)
        {
            continue;
        }

        // Max 10 sprites per line...
        if (ppu_get_context()->line_sprite_count >= 10)
        {
            break;
        }

        // This sprite is on the current line
        if (e.y <= cur_y + 16 && e.y + sprite_height > cur_y + 16)
        {
            oam_line_entry* entry = &ppu_get_context()->line_entry_array[
                ppu_get_context()->line_sprite_count++
            ];

            entry->entry = e;
            entry->next = NULL;

            if (!ppu_get_context()->line_sprites || ppu_get_context()->line_sprites->entry.x > e.x)
            {
                entry->next = ppu_get_context()->line_sprites;
                ppu_get_context()->line_sprites = entry;
                continue;
            }

            //Do some sorting...
            oam_line_entry* le = ppu_get_context()->line_sprites;
            oam_line_entry* prev = le;

            while (le)
            {
                if (le->entry.x > e.x)
                {
                    prev->next = entry;
                    entry->next = le;
                    break;
                }

                if (!le->next)
                {
                    le->next = entry;
                    break;
                }

                prev = le;
                le = le->next;
            }
        }
    }
}


void ppu_mode_oam()
{
    if (ppu_get_context()->line_ticks >= 80)
    {
        LCDS_MODE_SET(MODE_XFER);

        ppu_get_context()->pfc.cur_fetch_state = FS_TILE;
        ppu_get_context()->pfc.line_x = 0;
        ppu_get_context()->pfc.fetch_x = 0;
        ppu_get_context()->pfc.pushed_x = 0;
        ppu_get_context()->pfc.fifo_x = 0;
    }

    //Read OAM on the first tick only
    if (ppu_get_context()->line_ticks == 1)
    {
        ppu_get_context()->line_sprites = 0;
        ppu_get_context()->line_sprite_count = 0;

        load_line_sprites();
    }
}


void ppu_mode_xfer()
{
    pipeline_process();

    if (ppu_get_context()->pfc.pushed_x >= XRES)
    {
        pipeline_fifo_reset();

        LCDS_MODE_SET(MODE_HBLANK);

        if (LCDS_STAT_INIT(SS_HBLANK))
        {
            cpu_request_interrupt(IT_LCD_STAT);
        }
    }
}


void ppu_mode_vblank()
{
    if (ppu_get_context()->line_ticks >= TICKS_PER_LINE)
    {
        increment_ly();

        if (lcd_get_context()->ly >= LINES_PER_FRAME)
        {
            LCDS_MODE_SET(MODE_OAM);
            lcd_get_context()->ly = 0;
        }

        ppu_get_context()->line_ticks = 0;
    }
}


static u32 target_frame_time = 1000 / 60;
static long prev_frame_time = 0;
static long start_timer = 0;
static long frame_count = 0;


void ppu_mode_hblank()
{
    if (ppu_get_context()->line_ticks >= TICKS_PER_LINE)
    {
        increment_ly();

        if (lcd_get_context()->ly >= YRES)
        {
            LCDS_MODE_SET(MODE_VBLANK);

            cpu_request_interrupt(IT_VBLANK);

            if (LCDS_STAT_INIT(SS_VBANK))
            {
                cpu_request_interrupt(IT_LCD_STAT);
            }

            ppu_get_context()->current_frame++;

            //calc FPS...
            u32 end = get_ticks();
            u32 frame_time = end - prev_frame_time;

            if (frame_time < target_frame_time)
            {
                delay(target_frame_time - frame_time);
            }

            if (end - start_timer >= 1000)
            {
                u32 fps = frame_count;
                start_timer = end;
                frame_count = 0;

                printf("FPS: %d\n", fps);
            }

            frame_count++;
            prev_frame_time = get_ticks();
        }
        else
        {
            LCDS_MODE_SET(MODE_OAM);
        }

        ppu_get_context()->line_ticks = 0;
    }
}
