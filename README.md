# x86-assembly
A collection of baby C programs designed to be compiled and their .out files fed to the gdb for some assembly inspection

**README IN PROGRESS**

<p align="center">
  <img width="237" height="81" src="assem_prac_view_3.jpg">
</p>

x86 assembly. Fascinating...also Mind-numbing, sometimes at the same time. I couldn't find the exact resources I was looking for to delve into some simple c-to-assembly and assembly-to-c methods, I decided to create them myself. For all those looking to peruse a little assembly and see if they are on the right track, enjoy this repository. 

## From the Assempractice.c file

### sum function
Patience, skywalker.

### turnneg function
This function is designed to turn a positive number negative and a negative number...positive. In hindsight, I should have named it "flipsign". Oh well, here it is anyway:
```sh
int turnneg(int x)
{
    x = -x;
    return x;
}
```
And it's *annotated* assembly is not much longer:
```sh 
00401476 <_turnneg>:
  401476:	55                   	push   %ebp            #Set up the stack (push base pointer)
  401477:	89 e5                	mov    %esp,%ebp       #Move stack pointer to base pointer (set up continued)
  401479:	f7 5d 08             	negl   0x8(%ebp)       #Changes the sign of value in 0x8(%ebp)[local var x]
  40147c:	8b 45 08             	mov    0x8(%ebp),%eax  #Moves 0x8(%ebp)[local var x] into the %eax register
  40147f:	5d                   	pop    %ebp            #Pops base pointer from the stack 
  401480:	c3                   	ret                    #Returns
```
Just a nice thing to point out, for those unfamiliar with assembly, the %eax register is what I know as the "return" register. Return methods place their output in the %eax "locker", and the caller function consistently knows to pull the result of the called function out of the same %eax "locker".

### addten function
This function is a simple method designed to add 10 to a variable passed through parameters, and return this variable.
```sh
int addten(int x)
{
    int z = x + 10;
    return z;
}

```
I don't think it gets much simpler than this. Notice how I choose to create a new local variable and then return that variable in two different steps. However, the assembly shows that this action, while no different than "return x + 10;" to the c code, causes the assembly code to perform two extra data transfers that prove wasteful and inefficent. Here is the *annotated* assembly:
```sh
00401481 <_addten>:
  401481:	55                   	push   %ebp              #Set up the stack frame (push base pointer)
  401482:	89 e5                	mov    %esp,%ebp         #Move stack pointer to base pointer (still set up)
  401484:	83 ec 10             	sub    $0x10,%esp        #Subtract decimal 10 from stack pointer (space for variables)
  401487:	8b 45 08             	mov    0x8(%ebp),%eax    #Move 0x8(%esp)[local var x] to %eax register
  40148a:	83 c0 0a             	add    $0xa,%eax         #Add decimal 10 to %eax register
  40148d:	89 45 fc             	mov    %eax,-0x4(%ebp)   #Move result to -0x4(%ebp) [local var z]
  401490:	8b 45 fc             	mov    -0x4(%ebp),%eax   #Move that z right back into %eax register
  401493:	c9                   	leave                    #Clean up
  401494:	c3                   	ret                      #Return to main function
```
Lines 6 and 7 of this assembly function are completely unnecessary and wasting the code's time and space.

### divide function
To be continued.
### choice function
In progress.
### fibonacci function
Working on it.
### loop function
I'm a gettin there.


### main function
Here is the main function, where assempractice initializes a few local variables and proceeds to call all of the mini functions defined above it.
```sh
int main()
{
    int x = 10;
    int y = 3;
    int sumy, extraten, divided, chosen, fib;
    
    /*Adding together x = 10 and y = 3 */
    sumy = sum(x, y);
    /*Adding ten to x = 10 to make 20 */
    extraten = addten(x);
    /*Turning x = 20 into x = -20 */
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
```
I placed commentary above each function call clarifying the purpose and often the numeric inputs and results of each one to help a viewer stay on track. Now bear with me, this one is the longest of them all. Here is the *annotated* assembly function:
```sh
00401526 <_main>:
  401526:	55                   	push   %ebp                 #Pushes the base pointer onto the stack
  401527:	89 e5                	mov    %esp,%ebp            #Moves the stack pointer to the base pointer
  401529:	83 e4 f0             	and    $0xfffffff0,%esp     #Aligns the base pointer to the nearest multiple of 16
  40152c:	83 ec 30             	sub    $0x30,%esp           #Sets aside space on the stack for my global variables
  40152f:	e8 dc 05 00 00       	call   401b10 <___main>     
  401534:	c7 44 24 2c 0a 00 00 	movl   $0xa,0x2c(%esp)      #Moves the decimal value 10 into 0x2c(%esp) - a local variable x
  40153b:	00 
  40153c:	c7 44 24 28 03 00 00 	movl   $0x3,0x28(%esp)      #Moves decimal value 3 into 0x28(%esp) - a local variable y
  401543:	00 
  401544:	8b 44 24 28          	mov    0x28(%esp),%eax      #Moves 3 from y into the %eax register (the return register)
  401548:	89 44 24 04          	mov    %eax,0x4(%esp)       #Moves 3 from %eax into 0x4(%esp) - for future use by sum function
  40154c:	8b 44 24 2c          	mov    0x2c(%esp),%eax      #Moves 10 from x into %eax register
  401550:	89 04 24             	mov    %eax,(%esp)          #Moves 10 from %eax into (%esp) - for future use by sum function
  401553:	e8 08 ff ff ff       	call   401460 <_sum>        #Calls the sum function
  401558:	89 44 24 24          	mov    %eax,0x24(%esp)      #Moves sum result from %eax register to 0x24(%esp) - local var sumy
  40155c:	8b 44 24 2c          	mov    0x2c(%esp),%eax      #Moves x (still 10) from 0x2c(%esp) local var into %eax register
  401560:	89 04 24             	mov    %eax,(%esp)          #Moves x from %eax register into (%esp) - prep for addten function
  401563:	e8 19 ff ff ff       	call   401481 <_addten>     #Calls the addten function
  401568:	89 44 24 20          	mov    %eax,0x20(%esp)      #Moves addten result into 0x20(%esp) - local var extraten 
  40156c:	8b 44 24 2c          	mov    0x2c(%esp),%eax      #Moves x (x = 10) from 0x2c(%esp) into %eax register
  401570:	89 04 24             	mov    %eax,(%esp)          #Moves 10 from %eax into (%esp) - prep for turnneg function
  401573:	e8 fe fe ff ff       	call   401476 <_turnneg>    #Calls the turnneg function
  401578:	89 44 24 20          	mov    %eax,0x20(%esp)      #Moves -10 from %eax into 0x20(%esp) - the extraten local var
  40157c:	c7 44 24 2c 1e 00 00 	movl   $0x1e,0x2c(%esp)     #Moves decimal value 30 into 0x2c(%esp) - the x local var
  401583:	00 
  401584:	8b 44 24 28          	mov    0x28(%esp),%eax      #Moves the 3 from 0x28(%esp) [y local var] to %eax register
  401588:	89 44 24 04          	mov    %eax,0x4(%esp)       #Moves %eax register to 0x4(%esp) - prep for divide function
  40158c:	8b 44 24 2c          	mov    0x2c(%esp),%eax      #Moves 30 from 0x2c(%esp)[x local var] to the %eax register
  401590:	89 04 24             	mov    %eax,(%esp)          #Moves the %eax to (%esp) - prep for the divide function
  401593:	e8 fd fe ff ff       	call   401495 <_divide>     #Calls the divide function
  401598:	89 44 24 1c          	mov    %eax,0x1c(%esp)      #Moves result 10 from %eax register to 0x1c(%esp) - local var divided
  40159c:	c7 04 24 00 00 00 00 	movl   $0x0,(%esp)          #Moves decimal 0 into ($esp) - prep for choice function
  4015a3:	e8 02 ff ff ff       	call   4014aa <_choice>     #Calls the choice function
  4015a8:	89 44 24 18          	mov    %eax,0x18(%esp)      #Moves the result 1 in %eax register to 0x18(%esp) - local var chosen
  4015ac:	c7 04 24 05 00 00 00 	movl   $0x5,(%esp)          #Moves decimal value 5 into (%esp) - prep for fibonacci function
  4015b3:	e8 09 ff ff ff       	call   4014c1 <_fibonacci>  #Calls the fibonacci function
  4015b8:	89 44 24 14          	mov    %eax,0x14(%esp)      #Moves the result _ from %eax register into 0x14(%esp) - local var fib
  4015bc:	8b 44 24 2c          	mov    0x2c(%esp),%eax      #Moves 0x2c(%esp)[local var x = 30] into %eax register
  4015c0:	89 04 24             	mov    %eax,(%esp)          #Moves %eax register into (%esp) - prep for loop function
  4015c3:	e8 40 ff ff ff       	call   401508 <_loop>       #Calls the loop function
  4015c8:	89 44 24 2c          	mov    %eax,0x2c(%esp)      #Moves result 25 into 0x2c(%esp) - local var x
  4015cc:	b8 00 00 00 00       	mov    $0x0,%eax            #Moves decimal 0 into %eax register
  4015d1:	c9                   	leave                       #Restore the stack frame (see below for more info)
  4015d2:	c3                   	ret                         #return to previous function
  4015d3:	90                   	nop                         #Does nothing? (see below for more info)
  4015d4:	66 90                	xchg   %ax,%ax              #Looks like we are swapping %ax with... itself...multiple times?
  4015d6:	66 90                	xchg   %ax,%ax              #Apparently this is the same as a nop instruction
  4015d8:	66 90                	xchg   %ax,%ax
  4015da:	66 90                	xchg   %ax,%ax
  4015dc:	66 90                	xchg   %ax,%ax
  4015de:	66 90                	xchg   %ax,%ax
  ```
  This the mini main function assembly calls in the fifth line of the main section:
  ```sh
  00401b10 <___main>:                                       #I believe this is for establishing the global variables
  401b10:	a1 28 70 40 00       	mov    0x407028,%eax        #Please do not quote me on this part though
  401b15:	85 c0                	test   %eax,%eax
  401b17:	74 07                	je     401b20 <___main+0x10>
  401b19:	f3 c3                	repz ret 
  401b1b:	90                   	nop
  401b1c:	8d 74 26 00          	lea    0x0(%esi,%eiz,1),%esi
  401b20:	c7 05 28 70 40 00 01 	movl   $0x1,0x407028
  401b27:	00 00 00 
  401b2a:	eb 94                	jmp    401ac0 <___do_global_ctors>
  401b2c:	90                   	nop
  401b2d:	90                   	nop
  401b2e:	90                   	nop
  401b2f:	90                   	nop
  ```
  Note: For those of you (like me) who knows about popping for a stack but looked at the "leave" instruction with confusion, this is what stack overflow has to say:
  ```sh
  LEAVE is the counterpart to ENTER. The ENTER instruction sets up a stack frame by first pushing EBP onto the stack
  and then copies ESP into EBP, so LEAVE has to do the opposite, i.e. copy EBP to ESP and then restore the old EBP 
  from the stack.

See the section named PROCEDURE CALLS FOR BLOCK-STRUCTURED LANGUAGES in Intel's Software Developer's Manual Vol 1 
if you want to read more about how ENTER and LEAVE work.

enter n,0 is exactly equivalent to (and should be replaced with)

          push  %ebp
          mov   %esp, %ebp     # ebp = esp,  mov  ebp,esp in Intel syntax
          sub   $n, %esp       # allocate space on the stack.  Omit if n=0

leave is exactly equivalent to

          mov   %ebp, %esp     # esp = ebp,  mov  esp,ebp in Intel syntax
          pop   %ebp

Enter is very slow and compilers don't use it, but leave is fine. (http://agner.org/optimize). Compilers do use
leave if they make a stack frame at all (at least gcc does). But if esp is already equal to ebp, it's most 
efficient to just pop ebp.
```
Big thanks to [Michael](https://stackoverflow.com/users/1524450/michael) and [Peter](https://stackoverflow.com/users/224132/peter-cordes) for clearing that up for me. Also a shoutout to [Anthony Williams](https://stackoverflow.com/users/5597/anthony-williams) for clearing up the "nop" instruction:
```sh
NOPs serve several purposes:

They allow the debugger to place a breakpoint on a line even if it is combined with others in the generated code.
It allows the loader to patch a jump with a different-sized target offset.
It allows a block of code to be aligned at a particular boundary, which can be good for caching.
It allows for incremental linking to overwrite chunks of code with a call to a new section without having to
worry about the overall function changing size.
```
As for the xchg intstruction:
```sh
There are three variants of the xchg instruction:

    XCHG reg, reg
    XCHG reg, mem
    XCHG mem, reg
    
You can exchange data between registers or between registers and memory, but not from memory to memory:

        xchg    ax, bx       ; Put AX in BX and BX in AX
        xchg    memory, ax   ; Put "memory" in AX and AX in "memory"
        xchg    mem1, mem2   ; Illegal, can't exchange memory locations!
        
And remember that the xchg instruction does NOT accept immediate operands!
```
You lazy programmers - I'm doing all your stack overflow searching for you.
