#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>

//structure for items

struct items
{

  char items[20];
  float price;
  int qty;

};

//structure for orders

struct orders
{

  char customers[50];
  char date[30];
  int numOfItems;
  struct items itm[50];

};

//structure for ORDER-ID

struct orderid
{

  int id;
  char name[50];
  char date[11];
  float total;

};

//structure for EMPLOYEE INFORMATION

struct employee
{

  int empid;
  char empname[50];
  char emprole[20];
  int empsal;

};

//function to change foreground color:-

//to red

void red()
{
    printf("\033[0;31m");
}


void reset()
{
    printf("\033[0;34m");
}

//to green

void green()
{
    printf("\033[0;32m");
}

//to purple

void purple()
{
    printf("\033[0;35m");
}

//to yellow

void yellow()
{
    printf("\033[0;33m");
}

//to cyan

void cyan()
{
    printf("\033[0;36m");
}

//to white

void white()
{
    printf("\033[0;37m");
}

// function to convert integer to string

void tostring(char str[], int num)
{
    int i, rem, len = 0, n;

    n = num;
    while (n != 0)
    {
        len++;
        n /= 10;
    }
    for (i = 0; i < len; i++)
    {
        rem = num % 10;
        num = num / 10;
        str[len - (i + 1)] = rem + '0';
    }

    str[len] = '\0';
}

// Reverses a string 'str' of length 'len'

void reverse(char* str, int len)
{
    int i = 0, j = len - 1, temp;

    while (i < j)
    {
        temp = str[i];
        str[i] = str[j];
        str[j] = temp;
        i++;
        j--;
    }
}

// Converts a given integer x to string str[].
// d is the number of digits required in the output.
// If d is more than the number of digits in x,
// then 0s are added at the beginning.

int intToStr(int x, char str[], int d)

{
    int i = 0;

    while (x)
    {
        str[i++] = (x % 10) + '0';
        x = x / 10;
    }

    // If number of digits required is more, then
    // add 0s at the beginning

    while (i < d)
    {
        str[i++] = '0';
    }

    reverse(str, i);
    str[i] = '\0';
    return i;
}

// Converts a floating-point/double number to a string.

void ftoa(float n, char* res, int afterpoint)
{
  // Extract integer part

  int ipart = (int)n;

  // Extract floating part

  float fpart = n - (float)ipart;

  // convert integer part to string

  int i = intToStr(ipart, res, 0);

  // check for display option after point

  if (afterpoint != 0)
    {
    res[i] = '.'; // add dot

    // Get the value of fraction part upto given no.
    // of points after dot. The third parameter
    // is needed to handle cases like 233.007

    fpart = fpart * pow(10, afterpoint);

    intToStr((int)fpart, res + i + 1, afterpoint);
  }
}

// function to generate bill header

void generateBillHeader(char name[50], char date[30])

{
  printf("\n\n");
  printf("\t    FAMILY RESTAURANT");
  printf("\n\t    -----------------");
  printf("\nDate: %s", date);
  printf("\nInvoice To: %s", name);

  printf("\n");
  printf("---------------------------------------\n");
  printf("Items\t\t");
  printf("Qty\t\t");

  printf("Total\t\t");

  printf("\n---------------------------------------");
  printf("\n\n");
}

// function to generate body of the bill

void generateBillBody(char item[20], int qty, float price)

{

  printf("%s\t\t", item);
  printf("%d\t\t", qty);
  printf("  \t\t", qty * price);
  printf("\n");

}

// function to generate bill footer

void generateBillFooter(float total)

{

  printf("\n");
  float dis = 0.1 * total;
  float netTotal = total - dis;
  float cgst = 0.09 * netTotal, grandTotal = netTotal + 2 * cgst;

  printf("---------------------------------------\n");
  printf("Sub Total\t\t\t%0.2f", total);
  printf("\nDiscount @10%s\t\t\t%0.2f", "%", dis);

  printf("\n\t\t\t    -----------");

  printf("\nNet Total\t\t\t%0.2f", netTotal);
  printf("\nCGST @9%s\t\t\t%0.2f", "%", cgst);
  printf("\nSGST @9%s\t\t\t%0.2f", "%", cgst);
  printf("\n---------------------------------------\n");
  printf("Grand Total\t\t\t%0.2f", grandTotal);
  printf("\n---------------------------------------\n");

}
int main()
{

  float total;
  int opt, n, i, ordernumber=1;

  struct orders ord;
  struct orders order;
  struct orderid all_orders[50];
  struct employee empdata[20];

  // Defining Staff

  empdata[0].empid=1;
  strcpy(empdata[0].empname,"Rishabh");
  strcpy(empdata[0].emprole,"Cook");
  empdata[0].empsal=10000;

  empdata[1].empid=2;
  strcpy(empdata[1].empname,"Raveen");
  strcpy(empdata[1].emprole,"Waiter");
  empdata[1].empsal=2500;

  empdata[2].empid=3;
  strcpy(empdata[2].empname,"Daksh");
  strcpy(empdata[2].emprole,"Cook");
  empdata[2].empsal=10000;

  empdata[3].empid=4;
  strcpy(empdata[3].empname,"Gaurav");
  strcpy(empdata[3].emprole,"Chef");
  empdata[3].empsal=15000;

  int empcount=4;

  char saveBill = 'y', contFlag = 'y';
  char name[50];

  FILE *fp;

  time_t t = time(NULL);
  struct tm tm = *localtime(&t);

  // Initializing date

  int date[2];
  date[0]=tm.tm_mday;
  date[1]=tm.tm_mon + 1;
  date[2]=tm.tm_year + 1900;
  char date_str[11], day[3], month[3], year[5];
  tostring(day,date[0]);
  tostring(month,date[1]);
  tostring(year,date[2]);

  strcpy(date_str,day);
  strcat(date_str, "-");
  strcat(date_str,month);
  strcat(date_str, "-");
  strcat(date_str,year);

  // dashboard

  while (contFlag == 'y')
    {

    system("cls");
    float total = 0;
    int invoiceFound = 0;
    red();
    printf("\t============FAMILY RESTAURANT============");
    green();
    printf("\n\nPlease select your preferred operation:\t");
    yellow();
    printf("\n\n1.Generate Invoice");
    purple();
    printf("\n2.Show all Invoices");
    cyan();
    printf("\n3.Search Invoice");
    white();
    printf("\n4.Manage employees");
    purple();
    printf("\n5.Exit");
    reset();
    printf("\n\nYour choice: ");
    scanf("%d", &opt);
    fgetc(stdin);

    switch (opt)
    {

    case 1:
     {

      system("cls");
      all_orders[ordernumber].id=ordernumber;
      white();
      printf("\nPlease enter the name of the customer: ");
      reset();
      fgets(ord.customers, 50, stdin);
      ord.customers[strlen(ord.customers) - 1] = '\0';
      strcpy(all_orders[ordernumber].name,ord.customers);

      //   strcpy(ord.date, DATE);

      strcpy(ord.date, date_str);
      strcpy(all_orders[ordernumber].date, date_str);

      white();
      printf("\nPlease enter the number of items:");
      reset();
      scanf("%d", &n);
      ord.numOfItems = n;

      for (int i = 0; i < n; i++)
      {

        fgetc(stdin);
        printf("\n\n");

        yellow();
        printf("Please enter the item %d: ", i + 1);
        fgets(ord.itm[i].items, 20, stdin);
        ord.itm[i].items[strlen(ord.itm[i].items) - 1] = '\0';
        printf("Please enter the quantity: ");
        scanf("%d", &ord.itm[i].qty);
        printf("Please enter the unit price: ");
        scanf("%f", &ord.itm[i].price);
        total += ord.itm[i].qty * ord.itm[i].price;
        reset();

     }
    }

      generateBillHeader(ord.customers, ord.date);

      for (int i = 0; i < ord.numOfItems; i++)
      {
        generateBillBody(ord.itm[i].items, ord.itm[i].qty, ord.itm[i].price);
      }

      generateBillFooter(total);
      all_orders[ordernumber].total=(total*0.9)*1.18;

      ordernumber++;
      purple();
      printf("\nDo you want to save the invoice[y/n]: ");
      scanf("%s", &saveBill);
      reset();

      if (saveBill == 'y')

        {

        fp = fopen("RestaurentBill.txt", "a+");
        fprintf(fp,"\t    \tFAMILY RESTAURANT");

        fprintf(fp,"\n\t    \t-----------------");
        fprintf(fp,"\nDate: %s", ord.date);
        fprintf(fp,"\nInvoice To: %s", ord.customers);

        fprintf(fp,"\n");
        fprintf(fp,"---------------------------------------\n");
        fprintf(fp,"Items\t\t\t");

        fprintf(fp,"Qty\t\t");

        fprintf(fp,"Total");

        fprintf(fp,"\n---------------------------------------");
        fprintf(fp,"\n\n");

        for(i=0;i<n;i++)
        {

          fprintf(fp,ord.itm[i].items);

          if(strlen(ord.itm[i].items)>5)
          {

            fprintf(fp,"\t\t");

          }
          else
          {

            fprintf(fp,"\t\t\t");

          }

          char quantity[5];
          tostring(quantity,ord.itm[i].qty);
          fprintf(fp,quantity);
          fprintf(fp,"\t\t");
          char price[8];
          ftoa(ord.itm[i].price*ord.itm[i].qty,price,2);
          fprintf(fp,price);
          fprintf(fp,"\n");

        }

        fprintf(fp,"\n");

        char total_str[10];
        ftoa(total,total_str,2);
        char dis_str[10],netTotal_str[10],cgst_str[10],grtot_str[10];

        float dis = 0.1 * total;
        float netTotal = total - dis;
        float cgst = 0.09 * netTotal;
        float grandTotal = netTotal + 2 * cgst;
        ftoa(dis,dis_str,2);
        ftoa(netTotal,netTotal_str,2);
        ftoa(cgst,cgst_str,2);
        ftoa(grandTotal,grtot_str,2);

        fprintf(fp,"---------------------------------------\n");
        fprintf(fp,"Sub Total\t\t\t\t%s", total_str);
        fprintf(fp,"\nDiscount @10%s\t\t\t%s", "%", dis_str);
        fprintf(fp,"\n\t\t\t\t    ---------");
        fprintf(fp,"\nNet Total\t\t\t\t%s", netTotal_str);
        fprintf(fp,"\nCGST @9%s\t\t\t\t%s", "%", cgst_str);
        fprintf(fp,"\nSGST @9%s\t\t\t\t%s", "%", cgst_str);
        fprintf(fp,"\n---------------------------------------\n");
        fprintf(fp,"Grand Total\t\t\t\t%s", grtot_str);
        fprintf(fp,"\n---------------------------------------\n\n");

        fclose(fp);
      }

      break;

    case 2:

    {

      system("cls");

      for (i = 1; i < ordernumber; i++)
      {
        cyan();
        printf("ID: %d",all_orders[i].id);
        printf("\nName: %s",all_orders[i].name);
        printf("\nDate: %s",all_orders[i].date);
        printf("\nTotal Bill: %0.2f\n\n",all_orders[i].total);
        reset();
      }

      break;
    }

    case 3:

    {

      system("cls");
      int findid;
      yellow();
      printf("Enter the Order ID: ");
      reset();

      // fgetc(stdin);

      scanf("%d",&findid);

      if(all_orders[findid].id==findid)
      {

        green();
        printf("ID: %d",all_orders[findid].id);
        printf("\nName: %s",all_orders[findid].name);
        printf("\nDate: %s",all_orders[findid].date);
        printf("\nTotal Bill: %0.2f\n\n",all_orders[findid].total);
        reset();

      }

      else
      {
           red();
           printf("No Record found\n\n");
           reset();
      }


      break;

    }

    case 4:
    {

      int empopt;
      system("cls");

      yellow();
      printf("1.Add employee");
      printf("\n2.Remove employee");
      printf("\n3.Search employee");
      printf("\n4.Update employee details");
      printf("\n5.Show all employee data");
      reset();

      white();
      printf("\n\nSelect option: ");
      scanf("%d",&empopt);

      switch (empopt)

      {

      case 1:

        {

          int newid,salary,found;
          char newname[50],newrole[50];

          system("cls");

          while(1)
            {
            found=0;
            printf("Enter Employee ID: ");
            scanf("%d",&newid);
            for(i=0;i<empcount;i++)
            {

              if(newid==empdata[i].empid)
              {

                found=1;
                break;

              }

            }
            if(found)
            {

              red();
              printf("Employee ID already in use\n\n");
              reset();

            }
            else
            {

              empdata[empcount].empid=newid;
              break;

            }

          }

          purple();
          printf("Enter Employee name: ");
          scanf("%s",empdata[empcount].empname);
          printf("Enter Employee role: ");
          scanf("%s",empdata[empcount].emprole);
          printf("Enter Employee salary: ");
          scanf("%d",&empdata[empcount].empsal);

          reset();
          green();

          printf("\nSuccessfully added new employee!\n\n");
          reset();
          empcount++;

          break;

        }

      case 2:
        {
          int remid, found=0, j;

          system("cls");
          printf("Enter Employee ID: ");
          scanf("%d",&remid);

          for(i=0;i<empcount && !found;i++)
          {
            if(remid==empdata[i].empid)
            {
              found=1;
              for(j=i;j<empcount;j++)
              {

                empdata[j].empid=empdata[j+1].empid;
                strcpy(empdata[j].empname,empdata[j+1].empname);
                strcpy(empdata[j].emprole,empdata[j+1].emprole);
                empdata[j].empsal=empdata[j+1].empsal;

              }

              empcount--;
            }
          }
          if(!found)
          {

            red();
            printf("Employee not found\n\n");
            reset();

          }
          else
          {

              green();
              printf("\nSuccessfully removed employee data!\n\n");
              reset();

          }

          break;
        }

      case 3:
        {

          int searchid, found=0;
          system("cls");
          purple();
          printf("Enter Employee ID: ");
          scanf("%d",&searchid);

          for(i=0;i<empcount;i++)
          {

            if(searchid==empdata[i].empid)
            {

              found=1;
              printf("ID: %d",empdata[i].empid);
              printf("\nName: %s",empdata[i].empname);
              printf("\nRole: %s",empdata[i].emprole);
              printf("\nSalary: %d\n\n",empdata[i].empsal);

              break;

            }
          }
          if(!found)
           {

            red();
            printf("Employee not found\n\n");
            reset();

           }

          break;
        }

      case 4:
        {
          int updateid, found=0;
          system("cls");
          white();
          printf("Enter Employee ID: ");
          scanf("%d",&updateid);

          for(i=0;i<empcount;i++)
          {

            if(updateid==empdata[i].empid)
            {

              found=1;
              printf("Enter New Employee name: ");
              scanf("%s",empdata[i].empname);
              printf("Enter New Employee role: ");
              scanf("%s",empdata[i].emprole);
              printf("Enter New Employee salary: ");
              scanf("%d",&empdata[i].empsal);

              break;

            }
          }
          if(!found)
          {
              red();
              printf("Employee not found\n\n");
              reset();
          }

          else
          {
              green();
              printf("\nSuccessfully updated employee data!\n\n");
              reset();
          }

          break;
        }

      case 5:
        {

          system("cls");
          for(i=0;i<empcount;i++)
          {

           // blue();
            printf("ID: %d",empdata[i].empid);
            printf("\nName: %s",empdata[i].empname);
            printf("\nRole: %s",empdata[i].emprole);
            printf("\nSalary: %d\n\n",empdata[i].empsal);
            reset();

          }

          break;
        }

      default:
          {

             break;

          }

      }

      break;
    }

    case 5:
    {
      green();
      printf("\n\t\t Thank you!\n\n");
      reset();

      exit(0);
      break;
    }
    default:
    {

      red();
      printf("Sorry invalid option");
      reset();

      break;
    }

    }

    yellow();
    printf("Do you want to perform another operation[y/n]:\t");

    reset();
    scanf("%s", &contFlag);

  }

  green();
  printf("\n\t\t Thank you!\n\n");

  reset();
  printf("\n\n");

 return 0;

}
