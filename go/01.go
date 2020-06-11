package main

import (
	"fmt"
	"math"
)

func calculate_required_fuel(mass float64) float64 {
	return math.Floor(mass/3) - 2
}

func main() {
	result := calculate_required_fuel(12)
	fmt.Printf("result %f", result)
}
