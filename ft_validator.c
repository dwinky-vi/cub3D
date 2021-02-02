#include "ft_cub3d.h"

int     ft_check_r(t_window r)
{
    if (!(0 < r.size_x && r.size_x <= 1920))
        return (1);
    if (!(0 < r.size_y && r.size_y <= 1080))
        return (1);
    return (0);
}

char    *ft_validator(t_data *data)
{
    char *error;

    if (ft_check_r(data->config.r))
        return ("Error in window resolution (R)");
    
    return (NULL);
}