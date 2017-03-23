# contra-lang

Contra is a scripting language described in the book [Practical Interpreter Construction](https://leanpub.com/pic).

The book follows the implementation of the contra interpreter in Java, this implementation is in C.

### script example:
```
/*                                                                                 
 * fizzbuzz.con                                                                    
 */                                                                                
script                                                                             
    /*                                                                             
     * function to display msg                                                     
     */                                                                            
    def displayMsg(msg)                                                            
        println(msg)                                                               
    end                                                                            
                                                                                   
    // initialize count                                                            
    count = 1                                                                      
                                                                                   
    while count < 100
    
        if (count % 15) == 0                                                       
            displayMsg("FizzBuzz")                                                 
        end                                                                        
        else if (count % 3) == 0                                                   
            displayMsg("Fizz")                                                     
        end                                                                        
        else if (count % 5) == 0                                                   
            displayMsg("Buzz")                                                     
        end                                                                        
        else                                                                       
            displayMsg(count)                                                      
        end
        
        count = count + 1 /* increment counter */
        
    end                                                                            
end 
```
