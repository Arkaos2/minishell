/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saibelab <saibelab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 15:01:33 by saibelab          #+#    #+#             */
/*   Updated: 2025/12/12 17:54:18 by saibelab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 5
# endif

# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <string.h>
# include <fcntl.h>
# include <stdarg.h>

typedef struct s_gc t_gc;

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}					t_list;

typedef void	(*t_fonction)(va_list, int *);

typedef struct t_t_conversion
{
	char		c;
	t_fonction	f;
}	t_conversion;

int				ft_strncmp(const char *s1, const char *s2, size_t n);
int				ft_atoi(const char *str);
int				ft_isalpha(int c);
int				ft_isdigit(int c);
int				ft_isalnum(int c);
int				ft_isascii(int c);
int				ft_isprint(int c);
int				ft_toupper(int c);
int				ft_tolower(int c);
int				ft_memcmp(const void *s1, const void *s2, size_t n);
int				ft_lstsize(t_list *lst);
int				find_newline(char *str);
int				ft_strcmp(const char *s1, const char *s2);

char			*ft_strnstr(const char *str, const char *to_find, size_t n);
char			*ft_strdup(const char *s);
char			*ft_strchr(const char *str, int c);
char			*ft_strrchr(const char *s, int c);
char			*ft_substr(char const *s, unsigned int start, size_t len);
char			*ft_strjoin(char const *s1, char const *s2);
char			*ft_strtrim(char const *s1, char const *set);
char			*ft_itoa(int n);
char			*ft_strmapi(char const *s, char (*f)(unsigned int, char));
char			*get_next_line(int fd);
char			*read_to_stock(int fd, char *stock);
char			*extract_line(char *stock);
char			*remove_line(char *stock);
char			*append(char *stock, char *buf);
char			*create_new_stock(char *stock, char *new_stock, char *buf);
char			*ft_strncpy(char *dest, char *src, unsigned int n);
char			*ft_strndup(const char *s, int n);
char			*gc_strndup(t_gc *gc, const char *s, int n);

char			**ft_split(char const *s, char c);

void			free_split(char **tab);
void			ft_putstr_fd(char *s, int fd);
void			ft_putchar_fd(char c, int fd);
void			ft_putendl_fd(char *s, int fd);
void			ft_bzero(void *s, size_t n);
void			ft_putnbr_fd(int nbr, int fd);
void			ft_lstadd_front(t_list **lst, t_list *new);
void			ft_lstdelone(t_list *lst, void (*del)(void*));
void			ft_lstadd_back(t_list **lst, t_list *new);
void			ft_lstclear(t_list **lst, void (*del)(void *));
void			ft_lstiter(t_list *lst, void (*f)(void *));
void			ft_striteri(char *s, void (*f)(unsigned int, char *));
void			ft_putchar(char c, int *count);
void			ft_putnbr(int n, int *count);
void			ft_putstr(char *str, int *count);
void			print_decimal(va_list param, int *count);
void			putnbrhexa_low(unsigned long n, int *count);
void			putnbrhexa_up(unsigned long n, int *count);
void			print_string(va_list param, int *count);
void			print_char(va_list param, int *count);
void			unsigned_putnbr(unsigned int n, int *count);
void			print_unsigned(va_list param, int *count);
void			print_percent(va_list param, int *count);
void			print_hex_lower(va_list param, int *count);
void			print_hex_upper(va_list param, int *count);
void			print_pointer(va_list param, int *count);
int				ft_is_whitespace(char s);
int				ft_strncmp_custom(const char *s1, const char *s2, size_t n);
int				ft_strcmp_trim(const char *s1, const char *s2);
int				is_whitespace(char *s);

void			*ft_memchr(const void *arr, int c, size_t n);
void			*ft_calloc(size_t elementCount, size_t elementSize);
void			*ft_memcpy(void *dest, const void *src, size_t size);
void			*ft_memmove(void *dest, const void *src, size_t size);
void			*ft_memset(void *str, int ch, size_t n);

size_t			ft_strlcpy(char *dst, const char *src, size_t size);
size_t			ft_strlcat(char *dst, const char *src, size_t size);
size_t			ft_strlen(const char *s);

t_list			*ft_lstnew(void *content);
t_list			*ft_lstlast(t_list *lst);
t_list			*ft_lstmap(t_list *l, void *(*f)(void *), void (*del)(void *));

t_conversion	*init_table(void);
t_conversion	*find_key(char cle, t_conversion *table);

int				ft_printf(const char *str, ...);

long			ft_atol(const char *str);

#endif
