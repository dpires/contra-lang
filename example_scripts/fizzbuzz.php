<?php
    $count = 1;
    while ($count < 100) {
        if (($count % 15) == 0) {
            echo "FizzBuzz" . PHP_EOL;
        } else if (($count % 3) == 0) {
            echo "Fizz" . PHP_EOL;
        } else if (($count % 5) == 0) {
            echo "Buzz" . PHP_EOL;
        } else {
            echo $count . PHP_EOL;
        }
        $count = $count + 1;
    }
?>
