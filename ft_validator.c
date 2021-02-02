#include "ft_cub3d.h"

int     ft_check_r(t_window r)
{
    if (!(0 < r.size_x && r.size_x <= 1920))
        return (1);
    if (!(0 < r.size_y && r.size_y <= 1080))
        return (1);
    return (0);
}

int     ft_check_color(char *str)
{
    int num1;
    int num2;
    int num3;

    num1 = ft_atoi(str);
    if (!(0 <= num1 && num1 <= 255))
        return (1);
    while (ft_isdigit(*str))
        str++;
    while (!ft_isdigit(*str))
        str++;
    num2 = ft_atoi(str);
    if (!(0 <= num2 && num2 <= 255))
        return (1);
    while (ft_isdigit(*str))
        str++;
    while (!ft_isdigit(*str))
        str++;
    num3 = ft_atoi(str);
    if (!(0 <= num3 && num3 <= 255))
        return (1);
    return (0);
}

char    *ft_validator(t_data *data)
{
    char *error;

    if (ft_check_r(data->config.r))
        return ("Error in window resolution (R)");
    if (ft_check_color(data->config.f_str))
        return ("Error in floor color (F)");
    if (ft_check_color(data->config.c_str))
        return ("Error in floor color (C)");
    return (NULL);
}