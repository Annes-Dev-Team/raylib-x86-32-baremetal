#include "framebuffer.h"

BMFramebuffer bm_fb;

void BM_InitFramebuffer(MultibootInfo *mbi)
{
    if (!(mbi->flags & (1 << 12)))
        return;

    if (mbi->framebuffer_bpp != 32)
        return;

    if (mbi->framebuffer_type != 1)
        return;

    bm_fb.address = (volatile uint32_t *)
        (uintptr_t)mbi->framebuffer_addr;

    bm_fb.width  = mbi->framebuffer_width;
    bm_fb.height = mbi->framebuffer_height;
    bm_fb.pitch  = mbi->framebuffer_pitch;
    bm_fb.bpp    = mbi->framebuffer_bpp;
}

void BM_DrawPixel(int x, int y, uint32_t color)
{
    if (x < 0 || y < 0)
        return;

    if ((uint32_t)x >= bm_fb.width ||
        (uint32_t)y >= bm_fb.height)
        return;

    uint32_t *pixel = (uint32_t *)
        ((uintptr_t)bm_fb.address +
         (uintptr_t)y * bm_fb.pitch +
         (uintptr_t)x * 4);

    *pixel = color;
}

void BM_Clear(uint32_t color)
{
    for (uint32_t y = 0; y < bm_fb.height; y++)
    {
        for (uint32_t x = 0; x < bm_fb.width; x++)
        {
            BM_DrawPixel(x, y, color);
        }
    }
}
