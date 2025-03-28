#include "libpngps2.h"

void init_graphics(GSGLOBAL **gsGlobal, int width, int height) {
    *gsGlobal = gsKit_init_global();
    (*gsGlobal)->Mode = GS_MODE_NTSC;
    (*gsGlobal)->Interlace = GS_INTERLACED;
    (*gsGlobal)->Field = GS_FIELD;
    (*gsGlobal)->Width = width;
    (*gsGlobal)->Height = height;
    (*gsGlobal)->ZBuffering = GS_SETTING_ON;

    gsKit_init_screen(*gsGlobal);
    gsKit_mode_switch(*gsGlobal, GS_PERSISTENT);

    dmaKit_init(D_CTRL_RELE_OFF, D_CTRL_MFD_OFF, D_CTRL_STS_UNSPEC, D_CTRL_STD_OFF, D_CTRL_RCYC_8, 1 << DMA_CHANNEL_GIF);
    dmaKit_chan_init(DMA_CHANNEL_FROMSPR);
    dmaKit_chan_init(DMA_CHANNEL_TOSPR);
    dmaKit_chan_init(DMA_CHANNEL_GIF);
}

void load_texture(GSGLOBAL **gsGlobal, GSTEXTURE *texture, const unsigned char *data, unsigned int size, char PSM) {
    upng_t* upng = upng_new_from_bytes(data, size);
    if (upng != NULL) {
        upng_decode(upng);
        if (upng_get_error(upng) == UPNG_EOK) {
            texture->Width = upng_get_width(upng);
            texture->Height = upng_get_height(upng);
            texture->PSM = PSM;
            texture->Filter = GS_FILTER_NEAREST;
            texture->Vram = gsKit_vram_alloc(*gsGlobal, gsKit_texture_size(texture->Width, texture->Height, texture->PSM), GSKIT_ALLOC_USERBUFFER);
            texture->Mem = (u32*)memalign(128, gsKit_texture_size(texture->Width, texture->Height, texture->PSM));
            texture->ClutPSM = 0;
            texture->Clut = NULL;

            memcpy(texture->Mem, upng_get_buffer(upng), upng_get_size(upng));
            gsKit_texture_upload(*gsGlobal, texture);
        }
        upng_free(upng);
    }
}

void render_texture(GSGLOBAL *gsGlobal, GSTEXTURE *texture, int x, int y) {

    gsKit_clear(gsGlobal, GS_SETREG_RGBAQ(0x00, 0x00, 0x00, 0x80, 0x00));
    gsKit_prim_sprite_texture(gsGlobal, texture, x, y, 0.0f, 0.0f, texture->Width + x, texture->Height + y, texture->Width, texture->Height, 2, GS_SETREG_RGBAQ(0x80, 0x80, 0x80, 0x80, 0x00));
    gsKit_queue_exec(gsGlobal);
    gsKit_sync_flip(gsGlobal);

}

void FreeMemory(GSGLOBAL *gsGlobal, GSTEXTURE *texture) {
    free(texture->Mem);
    texture->Mem = NULL;
    gsKit_vram_clear(gsGlobal);
}
