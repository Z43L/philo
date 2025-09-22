# --- Nombre del ejecutable ---
NAME = philo

# --- Compilador y Flags ---
CC = gcc
# Flags de compilación: -Wall -Wextra -Werror para warnings, -g para debug
CFLAGS = -Wall -Wextra -Werror -g
# Flags de enlazado: -lreadline para la librería readline
LDFLAGS = -lreadline


# --- Directorios ---
# Directorio de los archivos fuente
SRC_DIR = .
# Directorio para los archivos objeto
OBJ_DIR = obj

# --- Archivos Fuente (.c) ---
# Lista de todos tus archivos .c en el directorio src/
SRCS_FILES =	philo.c utils.c philo2.c philo3.c philo4.c 
# Añade el prefijo del directorio a cada archivo fuente
SRCS = $(addprefix $(SRC_DIR)/, $(SRCS_FILES))

# --- Archivos Objeto (.o) ---
# Convierte la lista de archivos .c a .o y los coloca en el directorio obj/
OBJS = $(addprefix $(OBJ_DIR)/, $(SRCS_FILES:.c=.o))

# --- Reglas Principales ---

# Regla por defecto: compila todo
all: $(NAME)

# Regla para crear el ejecutable final
$(NAME): $(OBJS) 
	@echo "Enlazando los archivos objeto para crear $(NAME)..."
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME) $(LDFLAGS)
	@echo "¡PHILOOOOOOOOOOOOO compilado exitosamente!"

# Regla para compilar la librería libft
:
	@echo "Compilando la librería libft..."
	@$(MAKE) -s -C 

# --- Regla para compilar los archivos .c a .o ---
# Esta regla toma los archivos .c de src/ y crea los .o en obj/
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	@echo "Compilando $< -> $@"
	$(CC) $(CFLAGS) -I include -c $< -o $@

# --- Reglas de Limpieza ---

# Elimina los archivos objeto
clean:
	@echo "Eliminando archivos objeto..."
	@rm -rf $(OBJ_DIR)
	

# Elimina los objetos y el ejecutable
fclean: clean
	@echo "Eliminando el ejecutable $(NAME)..."
	@rm -f $(NAME)
	

# Recompila todo desde cero
re: fclean all

# --- Regla Phony ---
# Evita conflictos con nombres de archivos
.PHONY: all clean fclean re
