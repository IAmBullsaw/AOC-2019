package main

import (
       "fmt"
       "bufio"
       "os"
       "errors"
       "strings"
       "strconv"
)


func commaSplitFunc(data []byte, atEOF bool) (advance int, token []byte, err error) {
     if atEOF && len(data) == 0 {
        return 0, nil, nil
     }
     if i := strings.Index(string(data), ","); i >= 0 {
        return i + 1, data[0:i], nil
     }
     if i := strings.Index(string(data), "\n"); i >= 0 {
        return i + 1, data[0:i], nil
     }
     if atEOF {
        return len(data), data, nil
     }
     return
}

func operate(index int, intcode []int) (newIndex int, halt bool) {
     opcode := intcode[index]
     if opcode == 1 {
        pos1 := intcode[index + 1]
        pos2 := intcode[index + 2]
        pos3 := intcode[index + 3]
        intcode[pos3] = intcode[pos1] + intcode[pos2]
     } else if opcode == 2 {
        pos1 := intcode[index + 1]
        pos2 := intcode[index + 2]
        pos3 := intcode[index + 3]
        intcode[pos3] = intcode[pos1] * intcode[pos2]
     } else if opcode == 99 {
       return index, true
     }

     return index + 4, false
}

func main() {
     scanner := bufio.NewScanner(os.Stdin)
     scanner.Split(commaSplitFunc)
     text := ""
     opcode := 0
     var intcode []int
     err := errors.New("not an error")
     for scanner.Scan() {
         text = scanner.Text()
         opcode, err = strconv.Atoi(text)
         if err != nil {
            fmt.Println("ERROR", err)
            break;
         }
         intcode = append(intcode, opcode)
     }

     intcode[1] = 12//tmp fix
     intcode[2] = 2//tmp fix


     fmt.Println("before",intcode)
     index := 0
     halt := false
     for {
         index, halt = operate(index, intcode)
         if halt {
            break;
         }
     }
     fmt.Println("after", intcode)
}
