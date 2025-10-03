# LIBPNGPS2

Esta es una librería que cree para ps2sdk que te permite cargar imagenes png y renderizarlas de una forma sencilla usando el decodificar upng(Específicamente solo sirve para cargar imagenes png que esten en un buffer, se puede crear un archivo .c que almacene datos de una imagen usando [bin2c](https://github.com/gwilymk/bin2c.git))

## Ejemplo de código

```c
#include <libpngps2.h>
#include "datos.c" //Aquí deberías incluir el archivo generado con bin2c(puse de ejemplo datos.c)

int main()
{
    GSGLOBAL *gsGlobal;
    GSTEXTURE texture;

    init_graphics(gsGlobal, 320, 240); //La resolución de 320 x 240 es un ejemplo, pruebe con que resolución se rendereriza de forma correcta la imagen
    load_texture_from_buffer(gsGlobal, &texture, datos, size_datos, GS_PSM_CT32); //El PSM puede variar dependiendo de la imagen, tienes que probar con que PSM se renderiza correctamente, este puede ser GS_PSM_CT16, GS_PSM_CT24 o GS_PSM_CT32
    print_vram_usage(gsGlobal); //Función para poder ver el consumo de VRAM
    while(1)
    {
    draw_texture(gsGlobal, &texture, 0, 0);
    gsKit_queue_exec(gsGlobal);
    gsKit_sync_flip(gsGlobal);
    }

    return 0;
}
```

### Si quieres liberar memoria utiliza:

```c

FreeTexture(gsGlobal, &texture); //Puse como ejemplo "texture"
```

Recomiendo usar imagenes muy livianas y usar la resolución de 320 x 240(Es solo una recomendación)

## NOTA

El archivo cabecera de LIBPNGPS2 ya include los archivos cabecera gsKit.h, dmaKit.h y gsToolkit.h, asi que si incluyes libpngps2.h en tu código, ya no se necesita importar manualmente los archivos cabecera de gsKit, ya que al solo incluir libpngps2.h ya se importan :D

## Ejemplo de como incluir LIBPNGPS2 en un archivo Makefile

```make
EE_BIN = EXAMPLE_LIBPNGPS2.elf
EE_OBJS = main.o
EE_LIBS = -lkernel -ldebug -L$(PS2SDK)/ports/lib -lpngps2 -L$(GSKIT)/lib -lgskit -ldmakit
EE_INCS = -I$(PS2SDK)/ports/include -I$(GSKIT)/include

all: $(EE_BIN)
	$(EE_STRIP) --strip-all $(EE_BIN)

clean:
	rm -f $(EE_BIN) $(EE_OBJS)

include $(PS2SDK)/samples/Makefile.pref
include $(PS2SDK)/samples/Makefile.eeglobal	

```
### NOTA

Al incluir LIBPNGPS2 en tu Makefile, tienes que incluir tambien la librería gsKit, dmaKit y gsToolKit

## Instalación de la librería

### Dentro del directorio de LIBPNGPS2 escriba los siguientes comandos:

```
make
```

```
make install
```

La librería por defecto se instala en la carpeta ports de PS2SDK

### NOTA

La librería requiere el archivo cabecera de upng(específicamente upng.h) así que este archivo se copiara en la carpeta ports al momento de instalarla, ¡¡¡POR FAVOR NO LO ELIMINE!!!

## Para clonar el submodulo upng escribe los siguientes comandos dentro del directorio de LIBPNGPS2

```
git submodule init
```

```
git submodule update --recursive
```

## IMPORTANTE!!!!

### No debe compilar la librería usando versiones antiguas de ps2dev o de ps2sdk, recomiendo usar la ultima versión, ya que intenté compilar la librería en una versión vieja de ps2dev, y cuando cree una app muy simple usandola, se bugueaba la imagen, así que compilela en la ultima versión de ps2dev para evitar este fallo :D. Recomiendo compilarla en linux o WSL 


