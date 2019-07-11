/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   apply_color.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmerding <fmerding@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/24 04:34:23 by fmerding          #+#    #+#             */
/*   Updated: 2019/07/11 22:53:17 by fmerding         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

t_texture	black(t_texture tex)
{
	t_vec2 pos;

	pos.x = 0;
	pos.y = 0;
	while (pos.x < WIDTH)
	{
		while (pos.y < HEIGHT)
		{
			set_pixel(&tex, 0x000000ff, pos);
			pos.y++;
		}
		pos.y = 0;
		pos.x++;
	}
	return (tex);
}

// t_texture	red(t_texture tex, t_f *f, t_vec2 pos)
// {
// 	t_vec2 save;
// 	t_vec2 next;
//
// 	pos.x *= f->ppx;
// 	pos.y *= f->ppy;
// 	pos.x += 1;
// 	pos.y += 1;
// 	next.x = pos.x + f->ppx - 2;
// 	next.y = pos.y + f->ppy - 2;
// 	save = pos;
// 	while (pos.x < next.x)
// 	{
// 		while (pos.y < next.y)
// 		{
// 			set_pixel(&tex, 0xff0000ff, pos);
// 			pos.y++;
// 		}
// 		pos.y = save.y;
// 		pos.x++;
// 	}
// 	return (tex);
// }
//
t_texture	blacked(t_texture tex, t_p *p, t_vec2 pos)
{
	t_vec2 save;
	t_vec2 next;

	pos.y = pos.y * p->ppy;;
	next.x = pos.x + 500;
	next.y = pos.y + p->ppy;;
	save = pos;
	while (pos.x < next.x)
	{
		while (pos.y < next.y)
		{
			set_pixel(&tex,  0x000000ff, pos);
			pos.y++;
		}
		pos.y = save.y;
		pos.x++;
	}
	return (tex);
}

t_texture	blue(t_texture tex, t_p *p, t_vec2 pos, long l)
{
	t_vec2 save;
	t_vec2 next;

	if (l == 10000000000)
		return (tex);
	pos.y = pos.y * p->ppy;
	next.x = pos.x + p->ppx * l;
	next.y = pos.y + p->ppy;
	save = pos;
	while (pos.x < next.x)
	{
		while (pos.y < next.y)
		{
			set_pixel(&tex, 0x0066ffff, pos);
			pos.y++;
		}
		pos.y = save.y;
		pos.x++;
	}
	return (tex);
}

void	render(t_p *p)
{

	int		x;
	int		y;
	int		i;
	t_vec2	pos;
	t_vec2	pos2;
	//
	i = 0;
	x = 0;
	y = 0;

	while (i < p->size)
	{
		// while(x < WIDTH)
		// {
		pos.x = x;
		pos2.x = x + 500;
		pos.y = y;
		pos2.y = y;
		// if (p->a[i] == 10000000000)
		// 	*p->tex = blacked(*p->tex, p, pos);
		*p->tex = blue(*p->tex, p, pos, p->a[i]);
		// if (p->b[i] == 10000000000)
		// 	*p->tex = blacked(*p->tex, p, pos2);
		*p->tex = blue(*p->tex, p, pos2, p->b[i]);
		// }
		i++;
		y++;
	}
	update_image(p, p->tex);
}

void	apply(t_p *p)
{
	char *line;
	// int i;

	line = NULL;
	initialize_sdl(p);
	*p->tex = black(*p->tex);
	while (1)
	{
		while ((SDL_PollEvent(&(p->event))) != 0)
		{
			while ((get_next_line(0, &line) > 0))
			{
				if (operation(p, line) == -1)
				{
					free(line);
					ft_exit (1, p);
				}
				free(line);
				*p->tex = black(*p->tex);
				render(p);
				if (p->event.type == SDL_QUIT)
				{
					SDL_Quit();
					ft_exit(1, p);
				}
				if (p->event.type == SDL_KEYDOWN)
				{
					if (p->event.key.keysym.scancode == SDL_SCANCODE_ESCAPE)
					{
						SDL_Quit();
						ft_exit(1, p);
					}
				}
			}
			free(line);
			if (is_sorted(p->size, p->a) == 1)
				ft_putstr("OK\n");
			else
				ft_putstr("KO\n");
			sleep(5);
			SDL_Quit();
			ft_exit(1, p);
		}
	}
}
