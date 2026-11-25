/*
    images.h
*/

#ifndef _NIO_IMAGES_H
#define _NIO_IMAGES_H

#define MAX_IMAGES    (25)

SDL_Surface * get_image(int i_num);
void free_image(int i_num);
int load_image(char *file_name);

#endif /* _NIO_IMAGES_H */

