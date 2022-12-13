/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imustafa <imustafa@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 18:12:08 by imustafa          #+#    #+#             */
/*   Updated: 2022/12/13 14:48:07 by imustafa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

// free
void		free_scene_data(t_data *scene_data);
char		*free_memmory(char **ptr);
void		free_2d_array(double **arr, int size);

// get next line utils
char		*get_next_line(int fd);
char		*free_memmory(char **ptr);
char		*ft_strchr(const char *str, int c);
size_t		get_current_line_size(char *saved_line);

// Camera utils
t_point		calculate_to(t_data *scene_data);
t_vector	calculate_up(t_data *scene_data);
void		camera_transform(t_data *scene_data);

// Parse Error
int			check_for_a_c_l(char **info_split, t_data *scene_data);
int			check_for_sp_pl_cy(char **info_split, t_data *scene_data);

#endif