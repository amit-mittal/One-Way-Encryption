/*
 *project is made by:- amit mittal,11012304,IIT Guwahati
 *aim is to encrpyt any text
 *one way encryption
 */

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>


#define DIV_LIMIT 18491732913717
//divisor to smallen the flush number
#define MAX_LIMIT 18971484916821
//limit of flush
#define SIZE 128
//size of intermediate encrypted string
#define FINAL 16
//size of encrypted string which we want
#define LONG_PRIME 7
//this is the length of prime no. you want if string is very large
#define SHIFT 9
//this is by how much max we will shift the jumbled string
#define COPY 3
//this is by how much time our string is copied to jumble it

/*GLOBAL VARIABLES*/

long long int choice=0;//variable which stores what type of encryption user wants
long long int max_customize=127;//maximum value of encrypted character if choice is 3
long long int min_customize=33;//minimum value of encrypted character if choice is 3

/* FUNCTIONS*/

long long int sumofdigits(long long int n)//finds sum of digits
{
	long long int r,sum;
	sum=0;
	while(n>0)
	{
		r=n%10;
		sum+=r;
		n/=10;
	}
	return(sum);
}

long long flush(long long value)//to prevent data to cross the int limit
{
	if(value>MAX_LIMIT)
		value%=DIV_LIMIT;
	return value;
}

long long validate(long long int value)//validates into proper integer value of characters which you want in encrypted string
{
	if(choice==1)//encryption of type alphanumeric
	{
		value=abs(value);
		if(value>122)
		{
			value%=122;
			value=validate(value);
		}
		else if((value<48)&&(value>0))
		{
			while(value<122)
			{
				value*=2;
			}
			value/=2;
		}
		else if(((value>=58)&&(value<65))||((value<97)&&(value>90)))
			value+=sumofdigits(value);
			
		if(value<65||value>122||(value>90&&value<97))
		{
			value=65+sumofdigits(value);
			value=validate(value);
		}
	}
	else if(choice==2)//for encryption of general type
	{
		value=abs(value);
		if(value>127)
		{
			value%=127;
			value=validate(value);
		}
		else if((value<32)&&(value>0))
		{
			while(value<127)
			{
				value*=4;
			}
			value/=4;
		}
		else if(value==32)
			value=96;
		else if(value<=0)
			value=65;
	}
	else if(choice==3)//according to range of character what the user wants
	{		
		value=abs(value);
		
		if(value==0)
			value=1;
			
		if(value>max_customize)
		{
			value%=max_customize;
			value=validate(value);
		}
		else if(value<min_customize)
		{
			while(value<max_customize)
			{
				value*=2;
			}
			
			while(value>max_customize)
				value-=sumofdigits(value);
				
			value=validate(value);
		}
		
		if(value<min_customize||value>max_customize)
		{
			value=min_customize+(value%(max_customize-min_customize));
			value=validate(value);
		}
	}
	else//by default general type of encryption would occur
	{
		value=abs(value);
		if(value>127)
		{
			value%=127;
			value=validate(value);
		}
		else if((value<32)&&(value>0))
		{
			while(value<127)
			{
				value*=4;
			}
			value/=4;
		}
		else if(value==32)
			value=96;
		else if(value<=0)
			value=65;
	}
	
	return value;
}

long long int check_prime(long long int n)//check if number is prime or not
{
	long long int div;//divisor
	for(div=2;div<=(long long int)sqrt(n);++div)
	{
		if(n%div==0)
			return 0;
	}
	return 1;
}

long long int prime(long long int length,long long int count)//generate prime no.
{
	long long int start;//starting of checking
	long long int counter=0;//keep check on count
	start=pow(10,length-1)+1;
	
	for(;(counter<count)&&(start<pow(10,length));++start)
	{
		if(check_prime(start))
		{
			++counter;
		}
	}
	return(--start);
}

long long function_count_prime(char string[])//this generates which prime no. to take
{
	long long i;
	long long sum=0;//contains sum of characters
	
	for(i=0;i<strlen(string);++i)
	{
		sum+=string[i];
	}
	return sum;
}

long long function_zero(long long index)//this changes the zero entry of prime to some value
{
	long long int val;
	val=(index*index)+index+1;//function which is value to that corresponding zero
	return flush(val);
}

long long int function_array(long long int n)//this generates the array from a non-invertible function
{
	long long val;
	val=(n*n)-n+2;//that function
	return val;
}

long long int function_index(long long int n)//generates indices values
{
	long long int val;
	val=(n*n*n)+3*(n*n)-2*n+1;
	return val;
}

long long function_value_jumble(long long int n)//computes the necessary operations to jumble the string
{
	long long val;
	val=(3*n*n)+n+10;//function
	return val;
}

long long int function_jumble(char string[])//to jumble the encrypted text
{
	long long index;
	long sum=0;
	
	for(index=0;index<strlen(string);++index)
	{
		sum+=flush(function_value_jumble(string[index]+index));
	}
	
	while(sum>SHIFT)
	{
		sum=sumofdigits(sum);
	}
	return sum;
}

/* MAIN BODY*/

int main(int argc,char *argv[])
{

/* DECLARATION OF VARIABLES */

	long long int i=0,j,k,sum,sum_left,sum_right,temp;//use and throw vars
	char ch;//use and throw vars
	long long int value_prime,count_prime,sum_prime,length_prime,last_digit_prime,check_length_prime,length_string;//prime module
	char string_prime[SIZE];//string containing prime
	char new_string[SIZE];//temporary string
	long long int length;//string length
	long long int line;//no. of lines you wanna input
	long long int temp_length;//length of lines being inserted
	long long int total_char;//total no. of characters in whole text
	char *temp_string;//which is taking the input string
	char *string;//string to be encrypted
	long long int value_e_string;
	char e_string[FINAL];//encrypted string
	long long int value_array;
	long long int array[SIZE];//an array containing values generated by a function on the values of string
	long long int value_index;
	long long int index[SIZE];//an array containing values of function on index
	long long shift_jumble;//no. of places to shift
	char temp_jumble[COPY*FINAL];//jumble module
	FILE *input;//file pointer to input file containing our text


/* DATA BEING INPUT*/

	if(argc==2)//data being entered from file
	{
		i=0;
		input=fopen(argv[1],"r");
		
		if(input==NULL)
		{
			printf("Error in opening the file\n");
			return 0;
		}
		
		fscanf(input,"%lld",&length);
		getc(input);
		
		if(length<=SIZE)//manages memory allocation to the string to be encrypted
			string=malloc(SIZE*sizeof(char)); 
		else
		{
			sum=0;
			while(sum<length)
			{
				sum+=SIZE;
			}
			if(sum%(SIZE*2)==0)
				string=calloc((sum+2),sizeof(char));
			else
			{
				sum+=SIZE;
				string=calloc((sum+2),sizeof(char));
			}
		}
		
		ch=getc(input);
		while(ch!=EOF&&i<length)//reading the file till its end
		{
			string[i]=ch;
			ch=getc(input);
			++i;
		}
		string[i]='\0';
		length=strlen(string);
		
		fclose(input);
	}
	else//data being entered manually in terminal
	{
		printf("Enter no. of lines you want to input: ");//getting no. of lines
		scanf("%lld",&line);
	
		printf("Enter total characters in the whole text(excluding enter): ");
		scanf("%lld",&length);
		
		length=length+line-1;//adjust the length so as to adjust no. of lines
		
		if(length<=SIZE)//manages memory allocation to the string to be encrypted
			string=malloc(SIZE*sizeof(char)); 
		else
		{
			sum=0;
			while(sum<length)
			{
				sum+=SIZE;
			}
			if(sum%(SIZE*2)==0)
				string=calloc((sum+2),sizeof(char));
			else
			{
				sum+=SIZE;
				string=calloc((sum+2),sizeof(char));
			}
		}
	
		for(i=1;i<=line;++i)//getting all strings 
		{
			printf("Enter no. of characters you want to input in %lld line(excluding enter): ",i);
			scanf("%lld",&temp_length);
			getchar();//to flush extra enter
		
			temp_string=malloc((temp_length+2)*sizeof(char));//memory allocation to the particular string
		
			printf("Enter the %lld string you want to encrypt: ",i);
			fgets(temp_string,temp_length+2,stdin);//input string encrpted
			strcat(string,temp_string);//concatenate string
			free(temp_string);//free memory to temp_string
		}
		string[length]='\0';//modifying value of '\0'
		
		length=strlen(string);//to make sure that length being input was correct
	}
	
	printf("\nText to be encrypted: \n%s \n\n",string);
	
	printf("1.Alphanumeric\n2.General\n3.Customize\nEnter which type of encryption you want: ");
	
	scanf("%lld",&choice);//to get the choice of the user of type of encryption
	
	if(choice==3)//if choice is 3 then getting the min and max range of characters
	{
		printf("Enter the minimum ascii value of character you want for encryption(min is 33): ");
		scanf("%lld",&min_customize);
		
		printf("Enter the maximum ascii value of character you want for encryption(max is 127): ");
		scanf("%lld",&max_customize);
		
		if(max_customize>127)//checking if max does not get out of range
			max_customize=127;
			
		if(min_customize<33)//checking if min does not get out of range
			min_customize=33;
			
		if((min_customize>max_customize)||((min_customize<=33)&&(max_customize>=127)))//if min is greater than max and other conditions
		{
			min_customize=33;
			max_customize=127;
			choice=2;
		}
	}
	
/* PERFORM OPERATION TO GET A STRING OF REQD SIZE*/

	if(length<SIZE)//if length is less than to be encrypted string
	{
		length_string=length;//this is at the instant length of string
		
		while(length_string!=SIZE)//this loop runs until length becomes equal to size
		{
			check_length_prime=SIZE-length_string;//check the size of prime
			
			if(check_length_prime<LONG_PRIME)//works according to size of string
			{
				length_prime=SIZE-length_string;
			}
			else
			{
				length_prime=LONG_PRIME;
			}
			
			i=length_prime-1;
			
			//this is to generate those primes and store in that string
			count_prime=function_count_prime(string);//which prime no
			sum_prime=sumofdigits(count_prime);//sum of digits of prime
			value_prime=prime(length_prime,sum_prime);//that prime we want
			
			while(value_prime>0)//this is to get that prime in string
			{
				last_digit_prime=value_prime%10;
				if(last_digit_prime>0)
					string_prime[i]=last_digit_prime+'0';
				else
					string_prime[i]=validate(function_zero(i));
				value_prime/=10;
				--i;
			}
			string_prime[length_prime]='\0';
			strcat(string,string_prime);//concatenate the whole string
			length_string+=length_prime;
		}
	}
	else if(length>SIZE)//if length is more than to be encrypted string
	{		
		length_string=length;//this is at the instant length of string
		
		while(length_string!=sum)//this loop runs until length becomes equal to size
		{
			check_length_prime=sum-length_string;//check the size of prime
			
			if(check_length_prime<LONG_PRIME)//works according to size of string
			{
				length_prime=sum-length_string;
			}
			else
			{
				length_prime=LONG_PRIME;
			}
			
			i=length_prime-1;
			
			//this is to generate those primes and store in that string
			count_prime=function_count_prime(string);//which prime no
			sum_prime=sumofdigits(count_prime);//sum of digits of prime
			value_prime=prime(length_prime,sum_prime);//that prime we want
			
			while(value_prime>0)//this is to get that prime in string
			{
				last_digit_prime=value_prime%10;
				if(last_digit_prime>0)
					string_prime[i]=last_digit_prime+'0';
				else
					string_prime[i]=validate(function_zero(i));
				value_prime/=10;
				--i;
			}
			string_prime[length_prime]='\0';
			strcat(string,string_prime);//concatenate the whole string
			length_string+=length_prime;
		}
				
		k=0;//counter for new string
		j=0;//counter for the string
		
		temp=sum/(2*SIZE);//these many times i would run
		
		while(string[j]!='\0')//this is to get required size string
		{
			i=0;//keeps count on how much to do XOR
			
			sum_left=sum_right=0;
			//operation to get string of size SIZE
			while(i<temp)
			{
				++i;
				sum_left+=string[j];
				sum_left=flush(sum_left);
				++j;
			}
			
			i=0;
			
			while(i<temp)
			{
				++i;
				sum_right+=string[j];
				sum_right=flush(sum_right);
				++j;
			}
				
			sum=validate(sum_left^sum_right);
		
			new_string[k]=sum;//containing the edited string
			++k;
		}
		new_string[k]='\0';

		for(i=0;i<=SIZE;++i)//to get the string in the original string variable
			string[i]=new_string[i];
	}

	
	
/* DO ENCRYTION*/

	for(i=0;i<SIZE;++i)//to genrate the array of values as well as indices
	{
		value_array=function_array(string[i]);//calling that function which generates values
		array[i]=value_array;
		value_index=function_index(i);//calling function which genrates values for indices
		index[i]=value_index;
	}
	
	for(i=0;i<FINAL;++i)//this will do operation to encrypt the string
	{
		sum_left=sum_right=0;
		//operation to reduce size to FINAL
		for(j=i*(FINAL/2);j<(i*(FINAL/2))+(FINAL/4);++j)
		{
			sum_left+=flush(flush(array[j]+index[j])^string[j]);
		}
			
		for(;j<(i*(FINAL/2))+(FINAL/2);++j)
		{
			sum_right+=flush(flush(array[j]+index[j])^string[j]);
		}

		value_e_string=validate(flush(flush(sum_left)^flush(sum_right)));//this will generate that value
		
		e_string[i]=validate(value_e_string);
	}
	
/* JUMBLING THE ENCRYPTED TEXT*/

	for(i=0,j=0;i<COPY*FINAL;++i,++j)//copies string multiple times
	{
		j%=FINAL;
		temp_jumble[i]=e_string[j];
	}

	shift_jumble=function_jumble(e_string);//contains how much to shift
	
	for(i=shift_jumble,j=0;j<FINAL;++i,++j)//storing the jumbled string
	{
		e_string[i-shift_jumble]=temp_jumble[i];
	}
	e_string[FINAL]='\0';
	
	printf("\n\nEncrypted string: %s\n\n",e_string);//printing the final jumbled string
	
	free(string);
	
	return 0;	
} 
