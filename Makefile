NAME_1 = philo_one
NAME_2 = philo_two
NAME_3 = philo_three

all:
	$(MAKE) -C ./$(NAME_1)
	$(MAKE) -C ./$(NAME_2)
	$(MAKE) -C ./$(NAME_3)

clean :
	$(MAKE) -C ./$(NAME_1) clean
	$(MAKE) -C ./$(NAME_2) clean
	$(MAKE) -C ./$(NAME_3) clean

fclean :
	$(MAKE) -C ./$(NAME_1) fclean
	$(MAKE) -C ./$(NAME_2) fclean
	$(MAKE) -C ./$(NAME_3) fclean

re :
	$(MAKE) -C ./$(NAME_1) re
	$(MAKE) -C ./$(NAME_2) re
	$(MAKE) -C ./$(NAME_3) re

norminette :
	$(MAKE) -C ./$(NAME_1) norme
	$(MAKE) -C ./$(NAME_2) norme
	$(MAKE) -C ./$(NAME_3) norme

.PHONY: all clean fclean mclean re
