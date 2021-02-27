#ifndef HEAD_2D_H
# define HEAD_2D_H

void	set_hooks_2(t_vars *vars);

int		ft_func(t_vars *vars);

void	ft_display_map(t_vars *vars);

int		key_press_hook_2(int key, t_vars *vars);

int		key_release_hook_2(int key, t_vars *vars);

void	ft_step(t_vars *vars);

#endif