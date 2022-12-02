#ifndef PARSE_H
# define PARSE_H

# include "common.h"

//parcer utils
int check_file_name(char *file_name);
void replace_tabs_and_newline(char *line);
double parse_double(char *str);
int get_2darray_size(char **arr);
int parse_color(char *str ,  t_color *colors);
void free_2d_char_array(char **arr);
int skip_dot_verify_digits(char *str);


int parse_scene(char *file_name, t_data *scene_data);
int parse_camera(char **info, t_data *scene_data);
void parse_sphere(char **info, t_data *scene_data);
void parse_plane(char **info, t_data *scene_data);
void parse_cylinder(char **info, t_data *scene_data);
int parse_ambient_lighting(char **info, t_data *scene_data);

int parse_light(char **info, t_data *scene_data);

#endif