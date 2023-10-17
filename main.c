/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohayek <ohayek@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 19:01:05 by ohayek            #+#    #+#             */
/*   Updated: 2023/10/17 23:48:00 by ohayek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int worldMap[mapWidth][mapHeight]=
{
  {8,8,8,8,8,8,8,8,8,8,8,4,4,6,4,4,6,4,6,4,4,4,6,4},
  {8,0,0,0,0,0,0,0,0,0,8,4,0,0,0,0,0,0,0,0,0,0,0,4},
  {8,0,3,3,0,0,0,0,0,8,8,4,0,0,0,0,0,0,0,0,0,0,0,6},
  {8,0,0,3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,6},
  {8,0,3,3,0,0,0,0,0,8,8,4,0,0,0,0,0,0,0,0,0,0,0,4},
  {8,0,0,0,0,0,0,0,0,0,8,4,0,0,0,0,0,6,6,6,0,6,4,6},
  {8,8,8,8,0,8,8,8,8,8,8,4,4,4,4,4,4,6,0,0,0,0,0,6},
  {7,7,7,7,0,7,7,7,7,0,8,0,8,0,8,0,8,4,0,4,0,6,0,6},
  {7,7,0,0,0,0,0,0,7,8,0,8,0,8,0,8,8,6,0,0,0,0,0,6},
  {7,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,8,6,0,0,0,0,0,4},
  {7,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,8,6,0,6,0,6,0,6},
  {7,7,0,0,0,0,0,0,7,8,0,8,0,8,0,8,8,6,4,6,0,6,6,6},
  {7,7,7,7,0,7,7,7,7,8,8,4,0,6,8,4,8,3,3,3,0,3,3,3},
  {2,2,2,2,0,2,2,2,2,4,6,4,0,0,6,0,6,3,0,0,0,0,0,3},
  {2,2,0,0,0,0,0,2,2,4,0,0,0,0,0,0,4,3,0,0,0,0,0,3},
  {2,0,0,0,0,0,0,0,2,4,0,0,0,0,0,0,4,3,0,0,0,0,0,3},
  {1,0,0,0,0,0,0,0,1,4,4,4,4,4,6,0,6,3,3,0,0,0,3,3},
  {2,0,0,0,0,0,0,0,2,2,2,1,2,2,2,6,6,0,0,5,0,5,0,5},
  {2,2,0,0,0,0,0,2,2,2,0,0,0,2,2,0,5,0,5,0,0,0,5,5},
  {2,0,0,0,0,0,0,0,2,0,0,0,0,0,2,5,0,5,0,5,0,5,0,5},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,5},
  {2,0,0,0,0,0,0,0,2,0,0,0,0,0,2,5,0,5,0,5,0,5,0,5},
  {2,2,0,0,0,0,0,2,2,2,0,0,0,2,2,0,5,0,5,0,0,0,5,5},
  {2,2,2,2,1,2,2,2,2,2,2,1,2,2,2,5,5,5,5,5,5,5,5,5}
};

int access_spes_pixel(char *image_data, int tx, int ty, int bits_per_pixel, int size_line)
{
    char    *pixel;
    
    pixel = image_data + (ty * size_line + tx * (bits_per_pixel / 8));
    
    int color = *(int *)pixel;
    return color;
}

int texturePixels[7][texWidth * texHeight]; // Önceden yüklenmiş tekstür pikselleri

// Tekstür piksellerini yükleme fonksiyonu
void loadTexturePixels(void *texture, int textureIndex) {
    char *image_data;
    int bits_per_pixel, size_line, endian;
    image_data = mlx_get_data_addr(texture, &bits_per_pixel, &size_line, &endian);
    for (int y = 0; y < texHeight; y++) {
        for (int x = 0; x < texWidth; x++) {
            texturePixels[textureIndex][y * texWidth + x] = access_spes_pixel(image_data, x, y, bits_per_pixel, size_line);
        }
    }
}



void my_mlx_put_pixel_to_image(char *image_data, int x, int y, int bits_per_pixel, int size_line, int color)
{
    char *pixel = image_data + (y * size_line + x * (bits_per_pixel / 8));
    *(unsigned int *)pixel = color;
}

int main(void)
{
    // players data struct player
    int buffer[screenHeight][screenWidth];

    double  posX = 20.0, posY = 11.5;
    double  dirX = -1.0, dirY = 0.0;
    double  planeX = 0.0, planeY = 0.70;

    void    *texture[7];
    void    *mlx_ptr = mlx_init();
    void    *mlx_window = mlx_new_window(mlx_ptr, screenWidth, screenHeight, "cub3D");
    void    *mlx_image;
    char    *image_data;
    int bits_per_pixel1, size_line1, endian1;
    mlx_image = mlx_new_image(mlx_ptr, screenWidth, screenHeight);
    image_data = mlx_get_data_addr(mlx_image, &bits_per_pixel1, &size_line1, &endian1);
    for (int i = 0; i < screenHeight; i++)
    {
        for (int j = 0; j < screenWidth; j++)
            my_mlx_put_pixel_to_image(image_data, j, i, bits_per_pixel1, size_line1, 0x0);
    }
    int tw, th;
    texture[0] = mlx_xpm_file_to_image(mlx_ptr, "eagle.xpm", &tw, &th);
    texture[1] = mlx_xpm_file_to_image(mlx_ptr, "redbrick.xpm", &tw, &th);
    texture[2] = mlx_xpm_file_to_image(mlx_ptr, "purplestone.xpm", &tw, &th);
    texture[3] = mlx_xpm_file_to_image(mlx_ptr, "greystone.xpm", &tw, &th);
    texture[4] = mlx_xpm_file_to_image(mlx_ptr, "bluestone.xpm", &tw, &th);
    texture[5] = mlx_xpm_file_to_image(mlx_ptr, "mossy.xpm", &tw, &th);
    texture[6] = mlx_xpm_file_to_image(mlx_ptr, "wood.xpm", &tw, &th);
    for (int i = 0; i < 7; i++)
        loadTexturePixels(texture[i], i);
    
    for (int y = 0; y < screenHeight / 2; y++)
    {
        float rayDirX0 = dirX - planeX;
        float rayDirY0 = dirY - planeY;
        float rayDirX1 = dirX + planeX;
        float rayDirY1 = dirY + planeY;

        int p = y - screenHeight / 2;

        float posZ = 0.5 * screenHeight;
        
        float rowDistance = posZ / p;

        float floorStepX = rowDistance * (rayDirX1 - rayDirX0) / screenWidth;
        float floorStepY = rowDistance * (rayDirY1 - rayDirY0) / screenWidth;

        float   floorX = posX + rowDistance * rayDirX0;
        float   floorY = posY + rowDistance * rayDirY0;

        for (int x = 0; x < screenWidth; x++)
        {
            int cellX = (int)(floorX);
            int cellY = (int)(floorY);

            int tx = (int)(texWidth * (floorX - cellX)) & (texWidth - 1);
            int ty = (int)(texHeight * (floorY - cellY)) & (texHeight - 1);

            floorX += floorStepX;
            floorY += floorStepY;

            int floorTexture = 3;
            int ceilingTexture = 6;
            
            int floorColor = texturePixels[3][ty * texWidth + tx];
            int ceilingColor = texturePixels[6][ty * texWidth + tx];

            my_mlx_put_pixel_to_image(image_data, x, y, bits_per_pixel1, size_line1, floorColor);
            my_mlx_put_pixel_to_image(image_data, x, screenHeight - y - 1, bits_per_pixel1, size_line1, ceilingColor);
        }
    }
    for (int x = 0; x < screenWidth; x++)
    {
        double cameraX = 2 * x / (double)screenWidth - 1;
        double rayDirX = dirX + planeX * cameraX;
        double rayDirY = dirY + planeY * cameraX;

        int mapX = (int)posX;
        int mapY = (int)posY;

        double sideDistX;
        double sideDistY;

        double deltaDistX = (rayDirX == 0) ? 1e30 : fabs(1 / rayDirX);
        double deltaDistY = (rayDirY == 0) ? 1e30 : fabs(1 / rayDirY);
        double perpWallDist;

        int stepX;
        int stepY;

        int hit = 0;
        int side;

        if (rayDirX < 0)
        {
            stepX = -1;
            sideDistX = (posX - mapX) * deltaDistX;
        }
        else
        {
            stepX = 1;
            sideDistX = (mapX + 0.1 - posX) * deltaDistX;
        }
        if (rayDirY < 0)
        {
            stepY = -1;
            sideDistY = (posY - mapY) * deltaDistY;
        }
        else
        {
            stepY = 1;
            sideDistY = (mapY + 0.1 - posY) * deltaDistY;
        }
        while (hit == 0)
        {
            if (sideDistX < sideDistX)
            {
                sideDistX += deltaDistX;
                mapX += stepX;
                side = 0;
            }
            else
            {
                sideDistY += deltaDistY;
                mapY += stepY;
                side = 1;
            }
            if (worldMap[mapX][mapY] > 0) hit = 1;
        }
        if (side == 0) perpWallDist = (sideDistX - deltaDistX);
        else           perpWallDist = (sideDistY - deltaDistY);

        int lineHeight = (int)(10 * screenHeight / perpWallDist);

        int drawStart = -lineHeight / 2 + screenHeight / 2;
        if (drawStart < 0) drawStart = 0;
        int drawEnd = lineHeight / 2 + screenHeight / 2;
        if (drawEnd >= screenHeight) drawEnd = screenHeight - 1;
        int texNum = worldMap[mapX][mapY] - 1;
        double wallX; //where exactly the wall was hit
        if (side == 0) wallX = posY + perpWallDist * rayDirY;
        else           wallX = posX + perpWallDist * rayDirX;
        wallX -= floor((wallX));

        int texX = (int)(wallX * (double)(texWidth));
        if(side == 0 && rayDirX > 0) texX = texWidth - texX - 1;
        if(side == 1 && rayDirY < 0) texX = texWidth - texX - 1;

      // How much to increase the texture coordinate per screen pixel
        double step = 1.0 * texHeight / lineHeight;
      // Starting texture coordinate
        double texPos = (drawStart - screenHeight / 2 + lineHeight / 2) * step;
        for(int y = drawStart; y<drawEnd; y++)
        {
        // Cast the texture coordinate to integer, and mask with (texHeight - 1) in case of overflow
            int texY = (int)texPos & (texHeight - 1);
            texPos += step;
            int color = texturePixels[texNum][texWidth * texY + texX];
        //make color darker for y-sides: R, G and B byte each divided through two with a "shift" and an "and"
            if(side == 1) color = (color >> 1) & 8355711;
            my_mlx_put_pixel_to_image(image_data, x, y, bits_per_pixel1, size_line1, color);
      }
    }

    mlx_put_image_to_window(mlx_ptr, mlx_window, mlx_image, 0, 0);
    mlx_loop(mlx_ptr);
    mlx_destroy_image(mlx_ptr, mlx_image);
    
    return 0;
}
