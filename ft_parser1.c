#include "ft_cub3d.h"
#include "head_parser.h"

t_vars	ft_parse_data(int fd)
{
    t_vars      vars;
	char		*line;
	char		*tmp;
	t_list	    *list_map;
	int			r;

	line = NULL;
	vars.data.error = NULL;
	while ((r = get_next_line(fd, &line)) > 0)
	{
		tmp = line;
		line = ft_strtrim(line, " ");
		// написать отдельную функцию для проверки этого
		if (ft_strchr("RSFC", line[0]) && ft_strchr(" ", line[1]) || ft_strchr("NSWE", line[0]) && ft_strchr("OEA", line[1]))
        // if (ft_strchr("RNOSOWEEASFC", line[0]))
        {
            ft_set_config(&vars.data.config, line);
            free(tmp);
            free(line);
            continue;
        }
		else
			break ;
	}
	free(line);
	if (r <= 0)
	{
		vars.data.error = "Error in GNL";
		return (vars);
	}
	list_map = ft_make_list_map(fd, tmp);
	if (!list_map)
	{
		vars.data.error = "Error in list_map";
		return (vars);
	}
    vars.data.map = ft_convert_lst_to_matrix(&list_map);
	if (!vars.data.map)
	{
		vars.data.error = "Error in malloc in map";
		return (vars);
	}
	ft_find_person(&vars);
	return (vars);
}

