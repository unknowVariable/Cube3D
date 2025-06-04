/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alix <alix@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 05:15:00 by aconstan          #+#    #+#             */
/*   Updated: 2025/06/04 21:02:02 by alix             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

void put_pixel(t_config *conf, int x, int y, int color)
{
    char *dst;
    
    // Vérifications renforcées
    if (!conf || !conf->win.addr || x < 0 || x >= WIN_WIDTH || y < 0 || y >= WIN_HEIGHT)
        return;
        
    // Vérification d'alignement pour ARM
    if ((uintptr_t)conf->win.addr % sizeof(unsigned int) != 0) {
        fprintf(stderr, "Unaligned memory access!\n");
        return;
    }
    
    dst = conf->win.addr + (y * conf->win.line_len + x * (conf->win.bpp / 8));
    
    // Vérification que dst est dans les limites
    if (dst < conf->win.addr || dst >= conf->win.addr + (WIN_HEIGHT * conf->win.line_len))
        return;
        
    // Accès mémoire atomique
    volatile unsigned int *ptr = (volatile unsigned int *)dst;
    *ptr = color;
}
