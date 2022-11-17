#ifndef UTILS_H
# define UTILS_H


//error utils

//



// free

void free_scene_data(t_data *scene_data);
char	*free_memmory(char **ptr);
void free_2d_array(double **arr, int size);

// getnextline utils

char	*get_next_line(int fd);
char	*free_memmory(char **ptr);
char	*ft_strchr(const char *str, int c);
size_t	get_current_line_size(char *saved_line);


#endif