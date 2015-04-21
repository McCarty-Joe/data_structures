#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include "dynamicArray.h"


/* param: s the string
   param: num a pointer to double
   returns: true (1) if s is a number else 0 or false.
   postcondition: if it is a number, num will hold
   the value of the number
*/
int isNumber(char *s, double *num)
{
	char *end;
	double returnNum;

	if(strcmp(s, "0") == 0)
	{
		*num = 0;
		return 1;
	}
	else
	{
		returnNum = strtod(s, &end);
		/* If there's anythin in end, it's bad */
		if((returnNum != 0.0) && (strcmp(end, "") == 0))
		{
			*num = returnNum;
			return 1;
		}
	}
	return 0;  /*if got here, it was not a number*/
}

/*	param: stack the stack being manipulated
	pre: the stack contains at least two elements
	post: the top two elements are popped and
	their sum is pushed back onto the stack.
*/
void add (struct DynArr *stack)
{
	double x;
	double y;

	x = topDynArr(stack);
	popDynArr(stack);
	
	y = topDynArr(stack);
	popDynArr(stack);
	
	pushDynArr(stack, x + y);
}

/*	param: stack the stack being manipulated
	pre: the stack contains at least two elements
	post: the top two elements are popped and
	their difference is pushed back onto the stack.
*/
void subtract(struct DynArr *stack)
{
	double x;
	double y;

	x = topDynArr(stack);
	popDynArr(stack);

	y = topDynArr(stack);
    	popDynArr(stack);

	pushDynArr(stack, x - y);
}

/*	param: stack the stack being manipulated
	pre: the stack contains at least two elements
	post: the top two elements are popped and
	their quotient is pushed back onto the stack.
*/
void divide(struct DynArr *stack)
{
	double x;
	double y;

	x = topDynArr(stack);
	popDynArr(stack);

	y = topDynArr(stack);
	popDynArr(stack);

	pushDynArr(stack, y / x);
}


void multiply(struct DynArr *stack)
{
	double x;
	double y;

	x = topDynArr(stack);
	popDynArr(stack);

	y = topDynArr(stack);
	popDynArr(stack);

	pushDynArr(stack, x * y);
}
void power(struct DynArr *stack)
{
    	double x;
	double y;

	x = topDynArr(stack);
	popDynArr(stack);

	y = topDynArr(stack);
	popDynArr(stack);

	pushDynArr(stack, pow(y,x));
}
void square(struct DynArr *stack)
{
	double x;

	x = topDynArr(stack);
	popDynArr(stack);

	pushDynArr(stack, pow(x,2));
}

void cube(struct DynArr *stack)
{
	double x;

	x = topDynArr(stack);
	popDynArr(stack);

	pushDynArr(stack, pow(x,3));
}

void absv(struct DynArr *stack)
{
	double x;

	x = topDynArr(stack);
	popDynArr(stack);

	pushDynArr(stack, abs(x));
}

void squroot(struct DynArr *stack)
{
	double x;

	x = topDynArr(stack);
	popDynArr(stack);

	pushDynArr(stack, sqrt(x));
}

void exponential(struct DynArr *stack)
{
	double x;

	x = topDynArr(stack);
	popDynArr(stack);

	pushDynArr(stack, abs(x));
}

void natlog(struct DynArr *stack)
{
    	double x;

	x = topDynArr(stack);
	popDynArr(stack);

	pushDynArr(stack, log(x));
}

void logbase10(struct DynArr *stack)
{
	double x;

	x = topDynArr(stack);
	popDynArr(stack);

	pushDynArr(stack, log10(x));
}


double calculate(int numInputTokens, char **inputString)
{
	int i;
	double result = 0.0;
	char *s;
	struct DynArr *stack;
	double input;

	/*set up the stack*/
	stack = createDynArr(20);
	
	/*/ start at 1 to skip the name of the calculator calc*/
	for(i=1;i < numInputTokens;i++)
	{
		s = inputString[i];

		/*/ Hint: General algorithm:
		// (1) Check if the string s is in the list of operators.
		//   (1a) If it is, perform corresponding operations.
		//   (1b) Otherwise, check if s is a number.
		//     (1b - I) If s is not a number, produce an error.
		//     (1b - II) If s is a number, push./ it onto the stack*/

		if(strcmp(s, "+") == 0)
			add(stack);
		else if(strcmp(s,"-") == 0)
			subtract(stack);
		else if(strcmp(s, "/") == 0)
			divide(stack);
		else if(strcmp(s, "x") == 0)
			/* FIXME: replace printf with your own function */
			multiply(stack);
		else if(strcmp(s, "^") == 0)
			/* FIXME: replace printf with your own function */
			power(stack);
		else if(strcmp(s, "^2") == 0)
			/* FIXME: replace printf with your own function */
			square(stack);
		else if(strcmp(s, "^3") == 0)
			/* FIXME: replace printf with your own function */
			cube(stack);
		else if(strcmp(s, "abs") == 0)
			/* FIXME: replace printf with your own function */
			absv(stack);
		else if(strcmp(s, "sqrt") == 0)
			/* FIXME: replace printf with your own function */
			squroot(stack);
		else if(strcmp(s, "exp") == 0)
			/* FIXME: replace printf with your own function */
			exponential(stack);
		else if(strcmp(s, "ln") == 0)
			/* FIXME: replace printf with your own function */
			natlog(stack);
		else if(strcmp(s, "log") == 0)
			/* FIXME: replace printf with your own function */
			logbase10(stack);
        	else if(strcmp(s, "pi") == 0)
            		pushDynArr(stack, 3.14159265);
        	else if(strcmp(s, "e") == 0)
           	 	pushDynArr(stack, 2.7182818);
        	else if (isNumber(s, &input))
            		pushDynArr(stack, input);
        	else
        	{
            		printf("Error! Input contains invalid characters.");
        	}

    	}/*End for loop here*/



	if(sizeDynArr(stack) == 1)
        {
            printf(" = %g\n", topDynArr(stack));
            return result;
        }
        else
        {
            printf("ERROR!\n");
            return 0;
        }
}
int main(int argc , char** argv)
{
	/*/ assume each argument is contained in the argv array
	// argc-1 determines the number of operands + operators*/
	if (argc == 1)
		return 0;

	calculate(argc,argv);


	return 0;
}
