// Stage D

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Welcome Menu
void WelcomeScreen() 
{
    printf("\nWelcome to Tasty Burgers\nPlace your order here…\n1. Order Meals\n2. Order Burgers\n3. Order Chips\n4. Order Cold Drinks\n5. Process Order\n6. Cancel\n7. Exit\n\nSelect your option:"); 
}
void Burger_menu()
{
    printf("A - Chicken Burger - 15$\nB - Ham Burger - 17$\nC - Vegie Burger - 13$\nX - To return to Main Menu \n\n");
}
void Meals_menu()
{
    printf("A - Big Chicken Meal - 20$\nB - Big Ham Meal - 22$\nC - Big Vegie Meal - 18$\nX - To return to Main Menu");
}

typedef struct
{
    char chips_description;
    float min_weight;
}Chips_str;

typedef struct
{
    char drinks_description;
    float min_quantity;
}Drinks_str;

typedef struct 
{
    char receipt_no[6];
    int Burger_type;
    float Burgers_total;
    int B_Qty;
}Burger_Str;

typedef struct 
{
    float session_total;
    Burger_Str *Burgers;
    Chips_str *Chips;
    Drinks_str *Drinks;
}Meals_str;

typedef struct
{
    char receipt_No[6];
    float Total_Order_Value;
    Meals_str Meals;
    Chips_str Chips;
    Drinks_str Drinks;
}Order;

// Prototypes - Functions
Meals_str Meals_Ordering(float total, Meals_str Meals);
Burger_Str Burger_order(float total, Burger_Str Burger_main);
int Bill_Process(Burger_Str Burgers, Order Main);
Drinks_str Drinks_ordering(float Session_total, Drinks_str Drinks_main);
Chips_str Chips_ordering(float Session_total, Chips_str Chips_main);

// Main Functions
int main(){

    // Declare Variables
    int option, reciept_count=1, B_index=0, M_index=0, C_index=0, D_index=0;
    char receipt_num[5] = "B0001", R_Num[6];
    Burger_Str *Burgers, temp;
    Order *Orders;
    Meals_str *Meals, temp_m;
    Chips_str *Chips;
    Chips_str temp_c;
    Drinks_str *Drinks;
    Drinks_str temp_d;
    float Total_revnue = 0 ;

    // Password - check
    char password[12], pass[12]="TastyBurger";

    // Dynamic Memory Allocation
    Burgers = (Burger_Str*)malloc(sizeof(Burger_Str));
    Orders = (Order*)malloc(sizeof(Order));
    Meals = (Meals_str*)malloc(sizeof(Meals_str));
    Chips = (Chips_str*)malloc(sizeof(Chips_str));
    Drinks = (Drinks_str*)malloc(sizeof(Drinks_str));
    
    R_Num[5] = '\0';

    Orders[reciept_count].Total_Order_Value = 0;
    
    do
    {
       
        for (int i = 0; i < 5; i++)
        {
            Burgers[reciept_count].receipt_no[i] = receipt_num[i];
            Orders[reciept_count].receipt_No[i] = receipt_num[i]; 
        }
        Burgers[reciept_count].receipt_no[5] = '\0';
            
        printf("Reicept num (Online) : %s\n", Burgers[reciept_count].receipt_no);

        WelcomeScreen();
        scanf("%d", &option); 

        switch (option)
        {
        case 1: 
            // Meals Ordering

            if (M_index==0)
            {
                Meals[reciept_count] = Meals_Ordering(Orders[reciept_count].Total_Order_Value, Meals[reciept_count]);
            }else
            {
                temp_m = Meals_Ordering(Orders[reciept_count].Total_Order_Value, Meals[reciept_count]);
                Meals[reciept_count].Burgers = temp_m.Burgers;
                Meals[reciept_count].session_total = temp_m.session_total;
                temp_m = Meals[reciept_count+1];
            }
            Orders[reciept_count].Total_Order_Value = Orders[reciept_count].Total_Order_Value + Meals[reciept_count].session_total;
            M_index++;

            break;

        case 2:
            // Burger Odering

            if (B_index==0)
            {
                Burgers[reciept_count] = Burger_order(Orders[reciept_count].Total_Order_Value, Burgers[reciept_count]);
            }else
            {
                temp = Burger_order(Orders[reciept_count].Total_Order_Value, Burgers[reciept_count]);
                Burgers[reciept_count].B_Qty = temp.B_Qty;
                Burgers[reciept_count].Burger_type = temp.Burger_type;
                Burgers[reciept_count].Burgers_total = temp.Burgers_total;
                temp = Burgers[reciept_count+1];
            }
            Orders[reciept_count].Total_Order_Value = Orders[reciept_count].Total_Order_Value + Burgers[reciept_count].Burgers_total;
            B_index++;

            break;

        case 3:
            // Chips Ordering

            if (C_index==0)
            {
                Chips[reciept_count] = Chips_ordering(Orders[reciept_count].Total_Order_Value, Chips[reciept_count]);
            }else
            {
                temp_c = Chips_ordering(Orders[reciept_count].Total_Order_Value, Chips[reciept_count]);
                Chips[reciept_count].chips_description = temp_c.chips_description;
                Chips[reciept_count].min_weight = temp_c.min_weight;
                temp_c = Chips[reciept_count+1];
            }
            C_index++;
            Orders[reciept_count].Total_Order_Value = Orders[reciept_count].Total_Order_Value + Chips[reciept_count].chips_description;

            break;

        case 4:
            // Drinks Ordering

            if (D_index==0)
            {
                Drinks[reciept_count] = Drinks_ordering(Orders[reciept_count].Total_Order_Value, Drinks[reciept_count]);
            }else
            {
                temp_d = Drinks_ordering(Orders[reciept_count].Total_Order_Value, Drinks[reciept_count]);
                Drinks[reciept_count].drinks_description = temp_d.drinks_description;
                Drinks[reciept_count].min_quantity = temp_d.min_quantity;
                temp_d = Drinks[reciept_count+1];
            }
            D_index++;
            Orders[reciept_count].Total_Order_Value = Orders[reciept_count].Total_Order_Value + Drinks[reciept_count].drinks_description;

            break;
        case 5:
            // Proccess Order

            Total_revnue = Total_revnue + Bill_Process(Burgers[reciept_count], Orders[reciept_count]);
            Orders[reciept_count].Chips = Chips[reciept_count];
            Orders[reciept_count].Drinks = Drinks[reciept_count];
            Orders[reciept_count].Meals = Meals[reciept_count];

            reciept_count++;
            if (reciept_count>=10)
            {
                receipt_num[3] = (reciept_count / 10) + '0';
                receipt_num[4] = (reciept_count % 10) + '0';
            }
            else
            {
                receipt_num[3] = '0';
                receipt_num[4] = reciept_count + '0';
            }

            break;

        case 6:
            // Cancel - Proccess

            printf("Please enter your Receipt Number : ");
            scanf("%s", R_Num);

            printf("R num : %s", R_Num);

            for (int i = 0; i < reciept_count; i++)
            {
                printf("Before - %d : %s \n", i, Orders[i].receipt_No);
                if (R_Num[3] == Orders[i].receipt_No[3] && R_Num[4] == Orders[i].receipt_No[4])
                {
                    for (int x = i; x < reciept_count; x++)
                    {
                        Orders[i] = Orders[i + 1];
                        i++;
                    }
                    break;
                }
            }
            reciept_count = reciept_count - 1;

            break;

        case 7:

            printf("Thank You !\n");
            break;

        case 9:

            printf("\nEnter the Password: ");
            scanf("%s", password);

            if (strcmp(password, pass) == 0)
            {
                printf("Password Accepted\nTotal Revenue for today is: %.2f", Total_revnue);
            }
            else
            {
                printf("Invalid Password\n");
            }

            printf("\n<<Press Any Key to show the main meu >> \n");
            fflush(stdin);
            getchar();
            
            break;

        default:

            printf("Invalid Input");
            break;

        };

        if (reciept_count==26)
        {
            printf("\nReach maximum order count!\n");
            break;
        }

        
    } while (option!=7);

    return 0;
}


// Functions

// Burger Ordering
Burger_Str Burger_order(float total, Burger_Str Burger_main)
{
    Burger_Str Burgers;
    enum Burger_type{Chicken=1, Ham, Vegie};
    int Qty;
    char Burger_option, Dission;
    Burgers.B_Qty = 0;
    Burgers.Burgers_total = 0;
    do
    {
        Burger_menu();

        printf("Select your option: \n");
        scanf("%s", &Burger_option);

        switch (Burger_option)
        {
        case 'A':
            printf("You have selected Chicken Burger. How many burgers you wish you order? \n");
            scanf("%d", &Qty);
            Burgers.Burger_type = Chicken; 
            Burgers.Burgers_total = Burger_main.Burgers_total + Burgers.Burgers_total + 15*Qty;
            Burgers.B_Qty = Burgers.B_Qty + Qty;
            break;
        case 'B':
            printf("You have selected Ham Burger. How many burgers you wish you order? \n");
            scanf("%d", &Qty);
            Burgers.Burger_type = Ham; 
            Burgers.Burgers_total = Burger_main.Burgers_total + Burgers.Burgers_total + 17*Qty;
            Burgers.B_Qty = Burgers.B_Qty + Qty;
            break;
        case 'C':
            printf("You have selected Vegie Burger. How many burgers you wish you order? \n");
            scanf("%d", &Qty);
            Burgers.Burger_type = Vegie; 
            Burgers.Burgers_total = Burger_main.Burgers_total + Burgers.Burgers_total + 13*Qty;
            Burgers.B_Qty = Burgers.B_Qty + Qty;
            break;
        case 'X':
        case 'x':
            continue;
            break; 
        default:
            printf("Invalid Input! ");
            break;
        }

        printf("Your current bill value is $%.2f", total + Burgers.Burgers_total);
        printf("\nPress “Y” to add more meals into your order or Press “X” to go back to the previous menu.\n");
        fflush(stdin);
        Dission = getchar();

        if (Dission == 'X')
        {
            break;
        }

    } while (Burger_option != 'X');

    return Burgers;
}

// Meals Order
Meals_str Meals_Ordering(float total, Meals_str Meals_main)
{
    char Choice;
    const int Big_chicken = 20, Big_ham = 22, Big_vegie = 18;
    Meals_str Meals;
    Meals.session_total = 0;

    do
    {
        printf("A - Big Chicken Meal - 20$\nB - Big Ham Meal - 22$\nC - Big Vegie Meal - 18$\nX - To return to Main Menu \n");
        printf("Select your Meal type : ");
        scanf("%s", &Choice);

        switch (Choice)
        {
        case 'A':
            Meals.session_total = Meals_main.session_total + Meals.session_total +Big_chicken; 
            // total = total + Big_chicken;
            break;
        case 'B':
            Meals.session_total = Meals_main.session_total + Meals.session_total + Big_ham; 
            // total = total + Big_ham;
            break;
        case 'C':
            Meals.session_total = Meals_main.session_total + Meals.session_total + Big_vegie; 
            // total = total + Big_vegie;
            break;
        case 'x':
        case 'X':
            break;
        default:
            printf("Invalid Input !");
            break;
        };

        printf("Your current bill value is $%.2f\n\n", total + Meals.session_total);
        
        printf("Press “Y” to add more meals into your order or Press “X” to go back to the previous menu\n");
        fflush(stdin);
        Choice = getchar();

        if (Choice=='X')
        {
            break;
        }
        
    } while (Choice!='X');

    return Meals;
};

// Drinks Order
Drinks_str Drinks_ordering(float Session_total, Drinks_str Drinks_main)
{
    float total;
    Drinks_str Drinks;
    int qty;
    printf("You have selected Chips. How many chips you wish you order? ");
    scanf("%d", &qty);
    total = 3.50 * qty;
    Drinks.drinks_description = total;
    Drinks.min_quantity = qty;

    printf("Your current bill value is $%.2f\n", Session_total+total);

    return Drinks;
}

// Chips Order
Chips_str Chips_ordering(float Session_total, Chips_str Chips_main)
{
    float total;
    Chips_str Chips;
    int qty;
    printf("You have selected Chips. How many chips you wish you order? ");
    scanf("%d", &qty);
    total = 5 * qty;
    Chips.chips_description = total;
    Chips.min_weight = qty;

    printf("Your current bill value is $%.2f\n", Session_total+total);

    return Chips;
}

// Bill Proccess
int Bill_Process(Burger_Str Burgers, Order Main)
{
    float total, discount;

    if (Burgers.B_Qty>=5 && Main.Total_Order_Value>100)
    {
        discount = (Main.Total_Order_Value/100)*15;
        total = Main.Total_Order_Value - discount;
    }else if(Burgers.B_Qty>=5)
    {
        discount = (Main.Total_Order_Value/100)*10;
        total = Main.Total_Order_Value - discount;
    }
    else if(Main.Total_Order_Value>100)
    {
        discount = (Main.Total_Order_Value/100)*15;
        total = Main.Total_Order_Value - discount;
    }
    else
    {
        total = Main.Total_Order_Value;
    }
    
    printf("Your total bill value is $%.2f \n", Main.Total_Order_Value);
    printf("Discount 10%% - $%.2f \n", discount);
    printf("Final bill values is $%.2f \n", total);
    printf("Your receipt number is %s \n\n", Burgers.receipt_no);

    printf("<<Press Any Key to show the main meu >> \n");
    fflush(stdin);
    getchar();

    return total;
};
