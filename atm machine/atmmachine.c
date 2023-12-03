# include<stdio.h>
# include<stdlib.h>
# include<string.h>
void showmenu(int accountNum);
void showbalance(int accountNum);
struct accountDetails {
    char name[200];
    int accountNum;
    float balance;
    };

    void withdraw(int accountNum,int amount){
    FILE *fptr=fopen("account.txt","r");
    FILE *tempFile=fopen("temp.txt","w");
      
    struct accountDetails showd;
    int count = 0;

    while (fscanf(fptr, "%s %d %f", showd.name, &showd.accountNum, &showd.balance) != EOF) {

        if (showd.accountNum == accountNum) {
            count = 1;

            if (showd.balance >= amount) {

               showd.balance -= amount;

                fprintf(tempFile, "%s %d %.2f\n", showd.name, showd.accountNum,showd.balance );

                printf("Withdrawal successful. Remaining balance: %.2f\n", showd.balance);

            } else {
                fprintf(tempFile, "%s %d %.2f\n", showd.name, showd.accountNum, showd.balance);

                printf("Insufficient balance.\n");
            }
       } else {

            fprintf(tempFile, "%s %d %.2f\n", showd.name, showd.accountNum, showd.balance);
        
    }
    }
    
    fclose(fptr);
    fclose(tempFile);
    remove("account.txt");
    rename("temp.txt", "account.txt");
}
void loginAccount(){
    int accountNum;
    up1:

    printf("Enter Account Number: ");

    scanf("%d",&accountNum);
    int count=0;

    FILE *fptr=fopen("account.txt","r");
    struct accountDetails showd;
    while (fscanf(fptr, "%s %d %f",showd.name,&showd.accountNum,&showd.balance)!=EOF){

        if(showd.accountNum==accountNum){
            count =1;
            break;
        }
    } fclose(fptr);
    if(count){

        printf("login succesfully\n");
        showmenu(accountNum);
    }
    else{
        printf("Try again, invalid pin\n");
        goto up1;
    }

}   

    
void deposit(int accountNum, float amountnumber) {

    FILE *fptr = fopen("account.txt", "r");

    FILE *tempFile = fopen("temp.txt", "w");
    
    struct accountDetails showd;
    int count = 0;
    while (fscanf(fptr, "%s %d %f", showd.name, &showd.accountNum, &showd.balance) != EOF) {
        if (showd.accountNum == accountNum) {
            count = 1;
            showd.balance += amountnumber;

            fprintf(tempFile, "%s %d %.2f\n",showd.name, showd.accountNum, showd.balance);

            printf("Deposit successful. Updated balance: %.2f\n", showd.balance);
        } else {

            fprintf(tempFile, "%s %d %.2f\n", showd.name, showd.accountNum, showd.balance);
        }
    }
    
    fclose(fptr);
    fclose(tempFile);
    remove("account.txt");
    rename("temp.txt", "account.txt");
}
void createAccount(){
    FILE *fptr=fopen("account.txt","a");
    struct accountDetails detail;
     printf("enter your name :\n");
    scanf("%s",detail.name);

    printf("enter your account number : \n");
    scanf("%d",&detail.accountNum);

    detail.balance=0;
    fprintf(fptr, "%s %d %.2f\n",detail.name,detail.accountNum,detail.balance);

    fclose(fptr);
    printf("THANK YOU FOR CREATING ACCOUNT\n");

} 
    void showmenu(int accountNum){
        int option;
        do{
            printf("1. withdraw\n");
            printf("2. deposit\n");
            printf("3. balance\n");
            printf("4. quit\n");
            printf("enter the option\n");
            scanf("%d",&option);

            switch(option){
                case 1:{float amount;
                printf("please enter the amount to withdraw:\n");
                scanf("%f",&amount);
                withdraw(accountNum,amount);
                break;}
            
                case 2: {float amountnumber;
                printf("enter the number to be deposited :\n");
                scanf("%f",&amountnumber);
                deposit(accountNum,amountnumber);
                break;
                }
                case 3:
                showbalance(accountNum);
                break;
                case 4: 
                printf("THANK YOU\n");
                break;
                default:

                printf("try again\n");
            }
        }while(option !=4);
    }




void showbalance(int accountNum) {
    FILE *fptr = fopen("account.txt", "r");
    
    struct accountDetails showd;
    int count = 0;
    while (fscanf(fptr, "%s %d %f", showd.name, &showd.accountNum, &showd.balance) != EOF) {
     
        if (showd.accountNum == accountNum) {
            count = 1;
            printf("Current balance: %.2f\n", showd.balance);
            break;
        }
    }
    
    fclose(fptr);
    if (! count) {
        printf("Account not found.\n");
    }
}


int main(){
printf("********************   welcome to ATM service   *******************\n");
int option;
do{
    printf("1.Create Account\n");
    printf("2.Login\n");
    printf("3.Quit\n");
    printf("enter your option : ");
    scanf("%d",&option);
    switch (option){
        case 1: 
        //printf("THANK YOU SIR FOR CREATING YOUR ACCOUNT\n");
        createAccount();
        break;

        case 2: 
        printf("PLEASE ENTER YOUR LOGIN DETAILS\n");
        loginAccount();
        break;

        

       case 3:
       printf("THANK YOU\n");
       break;
        default :
        printf("TRY AGAIN\n");

    }

}while (option!=3);
    
    return 0;
}