# LIBFT
![](https://img.shields.io/badge/Language-C-blue)
![](https://img.shields.io/badge/School-42-black)

### I. How to use libft in you project:
<p>
<i>Clone repository</i>
<ol>
	git clone https://github.com/vscabell/libft.git<br />
</ol>
<p>
<i>Compile</i>
<ol>
	run make to compile libft.a<br />
	run make clean to delete tmp files after compile (only libft.a will be remain)<br />
	run make fclean to delete all files after compile<br />
	run make re to recompile all files<br />
</ol>
<p>
<i>Include</i>
<ol>
	#include "libft.h" in your project<br />
	compile libft.a<br />
	link you binary with -L./$(lib_path) -lft flag<br />
</ol>


### II. Function List

#### Functions from <ctype.h> library
|  Function | Synopsis  | Description |
| ------------ | ------------ | ------------ |
| ft_isalnum | int ft_isalnum(int c)  |  checks for an alphanumeric character |
| ft_isalpha |  int ft_isalpha(int c) |  checks for an alphabetic character |
| ft_isdigit | int ft_isdigit(int c)  |  checks for a digit (0 through 9) |
| ft_isprint | int ft_isprint(int c)  |  checks for any printable character including space |
| ft_isspace |  int ft_isspace(int c) |  checks for white-space characters |
| ft_tolower | int ft_tolower(int c)  |  upper case to lower case letter conversion |
| ft_toupper | ft_toupper(int c)  |  lower case to upper case letter conversion |

#### Functions from <stdlib.h> library
|  Function | Synopsis  | Description |
| ------------ | ------------ | ------------ |
|ft_atoi | int ft_atoi(const char *str)| convert ASCII string to an integer |
|ft_calloc | void *ft_calloc(size_t countsize_t size)| allocates size bytes and returns a pointer to the allocated memory

#### Functions from <string.h> library
|  Function | Synopsis  | Description |
| ------------ | ------------ | ------------ |
|ft_strlen|size_t ft_strlen(const char *s)| calculates the length of the string s, excluding the terminating null byteg|
|ft_strlcpy|size_t ft_strlcpy(char *dst, const char *src, size_t dstsize)|copies up to size - 1 characters from the NUL-terminated string src to dst, NUL-terminating the result|
|ft_strlcat|size_t ft_strlcat(char *dst, const char *src, size_t dstsize)| appends the NUL-terminated string src to the end of dst. It will append at most size - strlen(dst) - 1 bytes, NUL-terminating the result|
|ft_strchr|char *ft_strchr(const char *s, int c)| returns a pointer to the first occurrence of the character c in the string s|
|ft_strrchr|char *ft_strrchr(const char *s, int c)|returns a pointer to the last occurrence of the character c in the string s|
|ft_strnstr|char *ft_strnstr(const char *haystack, const char *needle,size_t len)| locate a substring in a string|
|ft_strncmp|int ft_strncmp(const char *s1, const char *s2, size_t n)| compares the two strings s1 and s2. It returns an integer less than, equal to, or greater than zero if s1 is found, respectively, to be less than, to match, or be greater than s2|
|ft_strdup|char *ft_strdup(const char *s1)| returns a pointer to a new string which is a duplicate of the string s|

#### Functions from <strings.h> library
|  Function | Synopsis  | Description |
| ------------ | ------------ | ------------ |
|ft_bzero|void ft_bzero(void *s, size_t n)| erases the data in the n bytes of the memory starting at the location pointed to by s, by writing zeroes (bytes containing '\0') to that area|
|ft_memset|void *ft_memset(void *b, int c, size_t len)| fills the first n bytes of the memory area pointed to by s with the constant byte c|
|ft_memchr|void *ft_memchr(const void *s, int c, size_t n)| locate byte in byte string|
|ft_memcpy|void *ft_memcpy(void *dst, const void *src, size_t n)| copies n bytes from memory area src to memory area dest. The memory areas must not overlap|
|ft_memccpy|void *ft_memccpy(void *dst, const void *src, int c, size_t n)| copies no more than n bytes from memory area src to memory area dest, stopping when the character c is found|
|ft_memcmp|int  ft_memcmp(const void *s1, const void *s2, size_t n)| returns an integer less than, equal to, or greater than zero if the first n bytes of s1 is found, respectively, to be less than, to match, or be greater than the first n bytes of s2|
|ft_memmove|void *ft_memmove(void *dst, const void *src, size_t len)| function copies n bytes from memory area src to memory area dest. The memory areas may overlap: copying takes place as though the bytes in src are first copied into a temporary array that does notoverlap src or dest, and the bytes are then copied from the temporary array to dest|

#### Non-standard functions
|  Function | Synopsis  | Description |
| ------------ | ------------ | ------------ |
|ft_substr|char *ft_substr(char const *s, unsigned int start, size_t len)|allocates (with malloc) and returns a substring from the string 's'. The substring begins at index 'start' and is of maximum size 'len'
|ft_strjoin|char *ft_strjoin(char const *s1, char const *s2)|allocates (with malloc) and returns a new string, which is the result of the concatenation of 's1' and 's2'
|ft_strtrim|char *ft_strtrim(char const *s1, char const *set)|allocates (with malloc) and returns a copy of 's1' with the characters specified in 'set' removed from the beginning and the end of the string
|ft_split|char **ft_split(char const *s, char c)|allocates (with malloc) and returns an array of strings obtained by splitting 's' using the character 'c' as a delimiter. The array must be ended by a NULL pointer
|ft_itoa|char *ft_itoa(int n)| allocates (with malloc) and returns a string representing the integer received as an argument. Negative numbers must be handled
|ft_strmapi|char *ft_strmapi(char const *s, char (*f)(unsigned int, char))|applies the function 'f' to each character of the string 's' to create a new string (with malloc) resulting from successive applications of 'f'
|ft_putchar_fd|void ft_putchar_fd(char c, int fd)|outputs the character 'c' to the given file descriptor
|ft_putstr_fd|void ft_putstr_fd(char *s, int fd)|outputs the string 's' to the given file descriptor
|ft_putendl_fd|void ft_putendl_fd(char *s, int fd)|outputs the string 's' to the given file descriptor, followed by a newline
|ft_putnbr_fd|void ft_putnbr_fd(int n, int fd)|outputs the integer 'n' to the given file descriptor

#### Linked list functions
|  Function | Synopsis  | Description |
| ------------ | ------------ | ------------ |
|ft_lstnew|t_list *ft_lstnew(void *content)| allocates (with malloc) and returns a new element. The variable 'content' is initialized with the value of the parameter 'content'. The variable 'next' is initialized to NULL.|
|ft_lstadd_front|void ft_lstadd_front(t_list **lst, t_list *new)| add new element at beginning of the list|
|ft_lstsize|int ft_lstsize(t_list *lst)| count the number of elements in a list|
|ft_lstlast|t_list *ft_lstlast(t_list *lst)| returns the last element of list|
|ft_lstadd_back|void ft_lstadd_back(t_list **lst, t_list *new)| add new element at end of the list|
|ft_lstdelone|void ft_lstdelone(t_list *lst, void (*del)(void*))| takes as a parameter an element and frees the memory of the element’s content using the function 'del' given as a parameter and free the element. The memory of 'next' must not be freed|
|ft_lstclear|void ft_lstclear(t_list **lst, void (*del)(void*))| deletes and frees the given element and every successor of that element, using the function 'del' and free. Finally, the pointer to the list must be set to NULL|
|ft_lstiter|void ft_lstiter(t_list *lst, void (*f)(void *))| iterates the list 'lst' and appllies the function 'f' to content of each element|
|ft_lstmap|t_list *ft_lstmap(t_list *lst, void *(*f)(void *), void(*del)(void *))| iterates the list 'lst' and appllies the function 'f' to content of each element. creates a new list resulting of the successive applications of the function 'f'. The 'del' function is used to delete the content of an element if needed |

Some other functions was added to this library in order to be used in future projects
