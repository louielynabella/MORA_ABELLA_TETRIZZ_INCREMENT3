#include <stdio.h>
#include <stdlib.h>


void game()
{
	int choice;
	

	system("cls");
				
	
	while(choice != 3)
	{
		system("cls");
		printf("Enter Mode to play");
		printf("\n[1] Solo Mode");
		printf("\n[2] Versus Mode");
		printf("\n[3] Why am I here?\n");
		
		printf("\nEnter your choice: ");
		scanf("%d", &choice);
		
		switch(choice)
		{
			case 1: 
			{
				system("cls");
				soloMode();
				system("cls");
				break;
			}
			case 2: 
			{
				system("cls");
				vsMode(); 
				break;
			}
			case 3:
			{
				system("cls");
				printf("Idk. You tell me....\n\n"); 
				exit(0); 
				break;
			}
			
			default: 
			{
				system("cls");
				printf("Not even in the choices, bud.\n\n"); 
				break;	
			}
		}
	}
	
	
	
}
