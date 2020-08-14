package main

import (
    "bufio"
    "fmt"
    "os"
    "strconv"
    "errors"
    "math"
)

func main() {
    scanner := bufio.NewScanner(os.Stdin)
    text := ""
    mass := 0
    err := errors.New("not an error")
    total_fuel := 0
    for scanner.Scan() {
        text = scanner.Text()
        mass, err = strconv.Atoi(text)
        if err != nil {
         fmt.Println(err)
         break;
        }

        module_fuel := 0
        for {
            mass = int(math.Floor(float64(mass)/3) - 2)
            if mass > 0 {
                module_fuel += mass
            } else {
                break;
            }
        }

        total_fuel += module_fuel
    }
    fmt.Println("total fuel:", total_fuel)
}
