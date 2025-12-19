#include <stdio.h>
#include <conio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_TRIES 3

struct Account
{
    char szFirstname[16];
    char szLastname[16];
    char szUsername[16];
    char szPassword[24];
    char szPhoneNo[14];
    char szDOB[12];
    char chGender;
};

int Menu(void);
void SignUp();
void Login();
void Forgot();
void Change();
void Display(struct Account);
void DeleteAccount();
void AcceptPassword(char *);
void CodeForDelete(char *);

int main(void)
{
    system("cls");
    while(1)
    {
        switch (Menu())
        {
        case 1:
            SignUp();
            break;
        case 2:
            Login();
            break;
        case 3:
            Forgot();
            break;
        case 4:
            Change();
            break;
        case 5:
            DeleteAccount();
            break;
        case 6:
            exit(0);

        default:
            printf("Invalid choice. Enter again\n");
        }
    }
}

int Menu(void)
{
    int iChoice;

    printf("MENU\n");
    printf("1. SignUp New User\n");
    printf("2. Existing User Login\n");
    printf("3. Forgot Username / Password\n");
    printf("4. Change Username / Password\n");
    printf("5. Delete my Account\n");
    printf("6. Exit\n");
    printf("\nEnter your choice\t:\t");
    scanf("%d", &iChoice);

    return iChoice;
}

void SignUp()
{
    char chTemp;
    char szPassword[15];
    struct Account oUser;

    printf("\nWelcome New User! Let's Create your Account\n\nEnter First Name\t:\t");
    scanf("%s", oUser.szFirstname);

    printf("Enter Last Name\t\t:\t");
    scanf("%s", oUser.szLastname);

    printf("Enter Username\t\t:\t");
    scanf("%s", oUser.szUsername);

    printf("Generate New Password\t:\t");
    fflush(stdin);
    AcceptPassword(oUser.szPassword);
Incorrect_Password:
    printf("\nConfirm Password\t:\t");
    fflush(stdin);
    AcceptPassword(szPassword);

    // scanf("%s", oUser.szPassword);
    if (strcmp(szPassword, oUser.szPassword) != 0)
    {
        printf("Incorrect Password. Try again\n");
        goto Incorrect_Password;
    }

    printf("\nEnter Date of Birth (DD/MM/YYYY)\t:\t");
    scanf("%s", oUser.szDOB);

    printf("Enter Phone Number\t:\t");
    scanf("%s", oUser.szPhoneNo);

    printf("Enter Gender\t\t:\t");
    fflush(stdin);
    scanf("%c", &oUser.chGender);

    FILE *pPtr = NULL;

    pPtr = fopen("UserLoginDetails.txt", "a");

    if (NULL == pPtr)
    {
        printf("\nError. Could not open file\n");
        return;
    }

    fprintf(pPtr, "%s %s %s %s %s %s %c\n", oUser.szUsername, oUser.szPassword, oUser.szFirstname, oUser.szLastname, oUser.szDOB, oUser.szPhoneNo, oUser.chGender);
    fclose(pPtr);

    printf("\nUser Account created successfully!!!\n");

    printf("Would you like to Sign in to your Account? (Y/N) :\t");
    fflush(stdin);
    scanf("%c", &chTemp);

    if (chTemp == 'Y' || chTemp == 'y')
        Login();
}

void Login()
{
    int iIndex;
    char chInput;
    int iFound = 0;
    int iChoice = 0;
    char szUsername[15];
    char szPassword[15];
    struct Account oTemp;

    printf("\n\nLOGIN TO YOUR ACCOUNT\n");

login:
    printf("Enter Username\t:\t");
    fflush(stdin);
    scanf("%s", szUsername);

    FILE *pPtr = NULL;

    pPtr = fopen("UserLoginDetails.txt", "r");

    if (NULL == pPtr)
    {
        printf("\nError. Could not open file\n");
        return;
    }

    while (fscanf(pPtr, "%s %s %s %s %s %s %c", &oTemp.szUsername, &oTemp.szPassword, &oTemp.szFirstname, &oTemp.szLastname, &oTemp.szDOB, &oTemp.szPhoneNo, &oTemp.chGender) == 7)
    {
        if (strcmp(szUsername, oTemp.szUsername) == 0)
        {
            iFound = 1;
            break;
        }
    }

    fclose(pPtr);

    if (iFound == 1)
    {
        while (iFound <= MAX_TRIES)
        {
            printf("Enter Password : ");
            AcceptPassword(szPassword);

            if (strcmp(szPassword, oTemp.szPassword) == 0)
            {
                printf("\nSuccessfully Logged In\n");
                Display(oTemp);
                return;
            }
            else
            {
                printf("\nIncorrect Password\nTry Again (%d Attempts Remaining)\n", MAX_TRIES - iFound++);
            }

            printf("\nShow Password? (Y/N) :\t");
            fflush(stdin);
            scanf("%c", &chInput);

            if (chInput == 'y' || chInput == 'Y')
            {
                printf("You entered\t:\t%s\n", szPassword);
            }
        }
    }
    else
    {
        printf("\nIncorrect Username\nWhat would you like to do :\n1. Re-enter Username\n2. Create New Account\n3. Forgot Username\n4. Exit\n");
        scanf("%d", &iChoice);

        if (iChoice == 1)
            goto login;
        else if (iChoice == 2)
            SignUp();
        else if (iChoice == 3)
            Forgot();
        else
            exit(0);
    }
}

void Display(struct Account oUser)
{
    char chChoice;
    printf("Welcome %s\n\nYour details are as follows :\n", oUser.szFirstname);
    printf("Username\t:\t%s\n", oUser.szUsername);
    printf("Password\t:\t%s\n", oUser.szPassword);
    printf("First Name\t:\t%s\n", oUser.szFirstname);
    printf("Last Name\t:\t%s\n", oUser.szLastname);
    printf("Date of Birth\t:\t%s\n", oUser.szDOB);
    printf("Mobile Number\t:\t%s\n", oUser.szPhoneNo);
    printf("Gender\t\t:\t%c\n\n", oUser.chGender);
    getch();
    printf("More Options\n1. Change Username/Password\n2. Logout\n");
    while (1)
    {
    printf("Enter Your Choice(1/2) : ");
    fflush(stdin);
    scanf("%c", &chChoice);

        if (chChoice == '1')
            Change();
        else if (chChoice == '2')
        {
            printf("Sign out successful !!\n\n");
            break;
        }
        else
            printf("Invalid Choice\n");

    }
    Menu();
}

void Forgot()
{
    char chChar;
    char szDOB[12];
    char szName[15];
    FILE *pPtr;
    struct Account oUser;

    printf("What would you like to know?\n1. Username\n2. Password\n3. Username and Password\nEnter your choice(1/2/3) : ");
    fflush(stdin);
    scanf("%c", &chChar);

DOB_again:

    printf("Enter your First Name : ");
    scanf("%s", &szName);
    printf("Enter Date Of Birth (dd/mm/yyyy) : ");
    scanf("%s", &szDOB);

    pPtr = fopen("UserLoginDetails.txt", "r");
    if (NULL == pPtr)
    {
        printf("Error opening file\n");
        return;
    }

    while (fscanf(pPtr, "%s %s %s %s %s %s %c", &oUser.szUsername, &oUser.szPassword, &oUser.szFirstname, &oUser.szLastname, &oUser.szDOB, &oUser.szPhoneNo, &oUser.chGender) == 7)
    {
        if (strcmp(szName, oUser.szFirstname) != 0)
            continue;

        if ((strcmp(szDOB, oUser.szDOB) == 0) && (strcmp(szName, oUser.szFirstname) == 0))
        {
            if (chChar == '1')
            {
                printf("\nUsername is : %s\n", oUser.szUsername);
                break;
            }
            else if (chChar == '2')
            {
                printf("\nPassword is : %s\n", oUser.szPassword);
                break;
            }
            else if (chChar == '3')
            {
                printf("\nUsername is : %s\nPassword is : %s", oUser.szUsername, oUser.szPassword);
                break;
            }
            else
            {
                printf("Invalid Input\n");
                return;
            }
        }
        else
        {
            printf("\nWrong Details. Try Again\n");
            goto DOB_again;
        }
    }
    fclose(pPtr);
}

void Change()
{
    char chFlag;
    char chChoice;
    int iCounter = 1;
    char szOldName[15];
    FILE *fpPtr = NULL;
    FILE *fpPtr1 = NULL;
    struct Account oUser;

    printf("What would you like to change?\n1. Username\n2. Password\nEnter your choice(1/2)\n");
    fflush(stdin);
    scanf("%c", &chChoice);

    fpPtr = fopen("UserLoginDetails.txt", "r");
    if (NULL == fpPtr)
    {
        printf("Error opening file\n");
        return;
    }
    // rewind(fpPtr);

Enter_Again:

    if (chChoice == '1')
    {
        printf("Enter your old username : ");
        scanf("%s", szOldName);
    }

    if (chChoice == '2')
    {
        printf("Enter your old password : ");
        AcceptPassword(szOldName);
    }

    while (fscanf(fpPtr, "%s %s %s %s %s %s %c", &oUser.szUsername, &oUser.szPassword, &oUser.szFirstname, &oUser.szLastname, &oUser.szDOB, &oUser.szPhoneNo, &oUser.chGender) == 7)
    {
        iCounter++;
        if (strcmp(szOldName, oUser.szUsername) == 0 || strcmp(szOldName, oUser.szPassword) == 0)
        {
            chFlag = '1';
            break;
        }
    }

    if (chFlag == '1')
    {
        fseek(fpPtr, 0, SEEK_SET);

        fpPtr1 = fopen("UserDetailsTempFile.txt", "w");
        if (NULL == fpPtr1)
        {
            printf("Could not open file\n");
            return;
        }

        while (--iCounter > 1)
        {
            fscanf(fpPtr, "%s %s %s %s %s %s %c", oUser.szUsername, oUser.szPassword, oUser.szFirstname, oUser.szLastname, oUser.szDOB, oUser.szPhoneNo, &oUser.chGender);
            fprintf(fpPtr1, "%s %s %s %s %s %s %c\n", oUser.szUsername, oUser.szPassword, oUser.szFirstname, oUser.szLastname, oUser.szDOB, oUser.szPhoneNo, oUser.chGender);
        }

        if (chChoice == '1')
        {
            printf("\nEnter New Userame : ");
            scanf("%s", szOldName);
        }
        if (chChoice == '2')
        {
            printf("\nEnter New Password : ");
            AcceptPassword(szOldName);
        }

        fscanf(fpPtr, "%s %s %s %s %s %s %c", oUser.szUsername, oUser.szPassword, oUser.szFirstname, oUser.szLastname, oUser.szDOB, oUser.szPhoneNo, &oUser.chGender);
        if (chChoice == '1')
            fprintf(fpPtr1, "%s %s %s %s %s %s %c", szOldName, oUser.szPassword, oUser.szFirstname, oUser.szLastname, oUser.szDOB, oUser.szPhoneNo, oUser.chGender);
        if (chChoice == '2')
            fprintf(fpPtr1, "%s %s %s %s %s %s %c", oUser.szUsername, szOldName, oUser.szFirstname, oUser.szLastname, oUser.szDOB, oUser.szPhoneNo, oUser.chGender);

        while (1)
        {
            chFlag = fgetc(fpPtr);
            if (chFlag == EOF)
                break;
            fputc(chFlag, fpPtr1);
        }

        fclose(fpPtr);
        fclose(fpPtr1);

        fpPtr = fopen("UserLoginDetails.txt", "w");
        if (NULL == fpPtr)
        {
            printf("Error Opening file\n");
            return;
        }

        fpPtr1 = fopen("UserDetailsTempFile.txt", "r");
        if (NULL == fpPtr1)
        {
            printf("Error Opening file\n");
            return;
        }

        while (1)
        {
            chFlag = fgetc(fpPtr1);
            if (chFlag == EOF)
                break;
            fputc(chFlag, fpPtr);
        }

        if (fpPtr != NULL)
        {
            fclose(fpPtr);
            fpPtr = NULL;
        }

        if (fpPtr1 != NULL)
        {
            fclose(fpPtr1);
            fpPtr1 = NULL;
        }

        remove("UserDetailsTempFile.txt");
        if (chChoice == '1')
            printf("Username changed successfully!\n");
        if (chChoice == '2')
            printf("Password changed successfully!\n");
    }
    else
    {
        printf("Incorrect username. Try Again\n");
        fseek(fpPtr, 0, SEEK_SET);
        goto Enter_Again;
    }
}

void DeleteAccount()
{
    int iFound = 0;
    char chChar;
    char szUsername[15];
    char szPassword[15];
    struct Account oTemp;

Username_Again:
    printf("Enter Username\t:\t");
    scanf("%s", szUsername);
    FILE *pPtr = NULL;

    pPtr = fopen("UserLoginDetails.txt", "r");

    if (NULL == pPtr)
    {
        printf("\nError. Could not open file\n");
        return;
    }

    while (fscanf(pPtr, "%s %s %s %s %s %s %c", &oTemp.szUsername, &oTemp.szPassword, &oTemp.szFirstname, &oTemp.szLastname, &oTemp.szDOB, &oTemp.szPhoneNo, &oTemp.chGender) == 7)
    {
        if (strcmp(szUsername, oTemp.szUsername) == 0)
        {
            iFound = 1;
            break;
        }
    }
    fclose(pPtr);

    if (iFound == 1)
    {
    Again:
        AcceptPassword(szPassword);

        if (strcmp(szPassword, oTemp.szPassword) == 0) //
        {
            printf("\nYour Account will be permanently deleted\nDo you want to proceed?(Y/N) : ");
            fflush(stdin);
            scanf("%c", &chChar);

            if (chChar == 'Y' | chChar == 'y')
            {
                CodeForDelete(szUsername);
            }

            else
                return;
        }
        else
        {
            printf("\nIncorrect Password. Try Again\n");
            goto Again;
        }
    }
    else
    {
        printf("\nIncorrect Username. Try Again\n");
        goto Username_Again;
    }
    remove("UserDetailsTempFile");
    printf("Account Deleted Successfully\n");
}

void AcceptPassword(char *szPassword)
{
    int iIndex;
    char chInput;

    // printf("Enter Password\t:\t");
    iIndex = 0;
    while (1)
    {
        chInput = getch();

        if (chInput == 13)
        {
            szPassword[iIndex] = '\0';
            break;
        }

        else if (chInput == 8)
        {
            if (iIndex > 0)
            {
                szPassword[iIndex--] = 0;
                printf("\b \b");
            }
        }

        else if (chInput == 9 || chInput == 32)
        {
            continue;
        }

        else
        {
            szPassword[iIndex++] = chInput;
            printf("*");
        }
    }
}

void CodeForDelete(char *szOldName)
{
    FILE *fpPtr;
    FILE *fpPtr1;
    char chFlag;
    int iCounter = 1;
    struct Account oUser;

    fpPtr = fopen("UserLoginDetails.txt", "r");
    if (NULL == fpPtr)
    {
        printf("Error opening file\n");
        return;
    }

    while (fscanf(fpPtr, "%s %s %s %s %s %s %c", &oUser.szUsername, &oUser.szPassword, &oUser.szFirstname, &oUser.szLastname, &oUser.szDOB, &oUser.szPhoneNo, &oUser.chGender) == 7)
    {
        iCounter++;
        if (strcmp(szOldName, oUser.szUsername) == 0)
        {
            chFlag = '1';
            break;
        }
    }

    if (chFlag == '1')
    {
        fseek(fpPtr, 0, SEEK_SET);

        fpPtr1 = fopen("UserDetailsTempFile.txt", "w");
        if (NULL == fpPtr1)
        {
            printf("Could not open file\n");
            return;
        }

        while (--iCounter > 1)
        {
            fscanf(fpPtr, "%s %s %s %s %s %s %c", oUser.szUsername, oUser.szPassword, oUser.szFirstname, oUser.szLastname, oUser.szDOB, oUser.szPhoneNo, &oUser.chGender);
            fprintf(fpPtr1, "%s %s %s %s %s %s %c\n", oUser.szUsername, oUser.szPassword, oUser.szFirstname, oUser.szLastname, oUser.szDOB, oUser.szPhoneNo, oUser.chGender);
        }

        fscanf(fpPtr, "%s %s %s %s %s %s %c\n", oUser.szUsername, oUser.szPassword, oUser.szFirstname, oUser.szLastname, oUser.szDOB, oUser.szPhoneNo, &oUser.chGender);

        while (1)
        {
            chFlag = fgetc(fpPtr);
            if (chFlag == EOF)
                break;
            fputc(chFlag, fpPtr1);
        }

        fclose(fpPtr);
        fclose(fpPtr1);

        fpPtr = fopen("UserLoginDetails.txt", "w");
        if (NULL == fpPtr)
        {
            printf("Error Opening file\n");
            return;
        }

        fpPtr1 = fopen("UserDetailsTempFile.txt", "r");
        if (NULL == fpPtr1)
        {
            printf("Error Opening file\n");
            return;
        }

        while (1)
        {
            chFlag = fgetc(fpPtr1);
            if (chFlag == EOF)
                break;
            fputc(chFlag, fpPtr);
        }

        if (fpPtr != NULL)
        {
            fclose(fpPtr);
            fpPtr = NULL;
        }

        if (fpPtr1 != NULL)
        {
            fclose(fpPtr1);
            fpPtr1 = NULL;
        }
    }
}