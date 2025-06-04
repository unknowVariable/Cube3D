/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alix <alix@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 05:15:00 by aconstan          #+#    #+#             */
/*   Updated: 2025/06/04 20:59:07 by alix             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

void put_pixel(t_config *conf, int x, int y, int color)
{
    char *dst;
    
    // Vérifications complètes
    if (!conf || !conf->win.addr || x < 0 || x >= WIN_WIDTH || y < 0 || y >= WIN_HEIGHT)
        return;
        
    // Calcul sécurisé de l'adresse
    dst = conf->win.addr + (y * conf->win.line_len + x * (conf->win.bpp / 8));
    
    // Protection supplémentaire
    if (dst >= conf->win.addr && dst < conf->win.addr + (WIN_HEIGHT * conf->win.line_len))
        *(unsigned int*)dst = color;
}
