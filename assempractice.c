typedef int bool;
#define true 1
#define false 0

int sum(int x, int y)
{
    return x + y;
}

int turnneg(int x)
{
    x = -x;
    return x;
}

int addten(int x)
{
    int z = x + 10;
    return z;
}

int divide(int x, int y)
{
    int z = x/y;
    return z;
}

bool choice(int x)
{
    if(x == 0)
        return true;
    else
        return false;
}

int fibonacci( int num)
{    if(num == 0)
        return 0;
    else if(num == 1)
        return 1;
    else
        return fibonacci(num-2) + fibonacci(num-1);
}

int loop(int x)
{   /* this loop goes from 0 to 4 */
    for(int i=0; i < 5; i++)
    {
        x = x - 1;
    }
    return x;
}

int main()
{
    int x = 10;
    int y = 3;
    int sumy, extraten, divided, chosen, fib;
    
    /*Adding together x = 10 and y = 3 */
    sumy = sum(x, y);
    /*Adding ten to x = 10 to make extraten = 20 */
    extraten = addten(x);
    /*Turning x = 10 into extraten = -10 */
    extraten = turnneg(x);
    /* Making x = 30 and dividing by y = 3 */
    x = 30;
    divided = divide(x, y);
    /* Testing choice with a 0 input */
    chosen = choice(0);
    /* fibonacci testing here with input 5 */
    fib = fibonacci(5);
    /* Looping- should subtract 4 from x = 10 */
    x = loop(x);

}