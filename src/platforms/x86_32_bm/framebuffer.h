#ifndef BM_FRAMEBUFFER_H
#define BM_FRAMEBUFFER_H

#include <stdint.h>

typedef struct __attribute__((packed))
{
    uint32_t flags;

    uint32_t mem_lower;
    uint32_t mem_upper;
    uint32_t boot_device;
    uint32_t cmdline;

    uint32_t mods_count;
    uint32_t mods_addr;

    uint8_t  syms[16];

    uint32_t mmap_length;
    uint32_t mmap_addr;

    uint32_t drives_length;
    uint32_t drives_addr;

    uint32_t config_table;
    uint32_t boot_loader_name;
    uint32_t apm_table;

    uint32_t vbe_control_info;
    uint32_t vbe_mode_info;
    uint16_t vbe_mode;
    uint16_t vbe_interface_seg;
    uint16_t vbe_interface_off;
    uint16_t vbe_interface_len;

    uint64_t framebuffer_addr;
    uint32_t framebuffer_pitch;
    uint32_t framebuffer_width;
    uint32_t framebuffer_height;
    uint8_t  framebuffer_bpp;
    uint8_t  framebuffer_type;

    uint8_t color_info[6];
} MultibootInfo;

typedef struct
{
    volatile uint32_t *address;
    uint32_t width;
    uint32_t height;
    uint32_t pitch;
    uint8_t bpp;
} BMFramebuffer;

extern BMFramebuffer bm_fb;

void BM_InitFramebuffer(MultibootInfo *mbi);
void BM_Clear(uint32_t color);
void BM_DrawPixel(int x, int y, uint32_t color);

#endif