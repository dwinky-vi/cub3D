#include "ft_cub3d.h"

int     ft_check_r(t_window r)
{
    if (!(0 < r.size_x && r.size_x <= 1920))
        return (1);
    if (!(0 < r.size_y && r.size_y <= 1080))
        return (1);
    return (0);
}

int     ft_get_color(int num1, int num2, int num3)
{
    int color;

    color = 0;
    color = color | num1;
    color = color << 8;
    color = color | num2;
    color = color << 8;
    color = color | num3;
    return (color);
}

int     ft_check_and_get_color(char *str, int *color)
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
    *color = ft_get_color(num1, num2, num3);
    return (0);
}

int     ft_check_path(char *path)
{
    int fd;

    fd = open(path, O_RDONLY);
    if (fd == -1)
        return (1);
    close(fd);
    return (0);
}

int     ft_checking_map(char **map)
{
    // int k;
    // int j;

    // j = 0;
    // while (map[0][j])
    // {
    //     if (map[0][j] == '0')
    //         return (1);
    // }
    // k = 0;
    // while (map[k])
    // {
    //     j = 0;
    //     if (map[k][0] == '0')
    //         return (1);
    //     j = ft_strlen(map[k]) - 1;
    //     if (j > map[k][--j] == '0')
    //         return (1);
    //     k++;
    // }
    // j = 0;
    // k--;
    // while (map[k][j])
    // {
    //     if (map[0][j] == '0')
    //         return (1);
    // }
    return (0);
}

char    *ft_validator(t_data *data)
{
    char *error;

    if (ft_check_r(data->config.r))
        return ("Error in window resolution (R)");
    if (ft_check_and_get_color(data->config.f_str, &(data->config.f_int)))
        return ("Error in floor color (F)");
    if (ft_check_and_get_color(data->config.c_str, &(data->config.c_int)))
        return ("Error in floor color (C)");
    // if (ft_check_path(data->config.no))
    //     return ("Error in path (NO)");
    // if (ft_check_path(data->config.so))
    //     return ("Error in path (SO)");
    // if (ft_check_path(data->config.we))
    //     return ("Error in path (WE)");
    // if (ft_check_path(data->config.ea))
    //     return ("Error in path (EA)");
    // if (ft_check_path(data->config.s))
    //     return ("Error in path (S)");
    // if (ft_checking_map(data->map))
    //     return ("Error \nInvalid map");
    return (NULL);
}