package 01

import {
  "fmt"
  "math"
}

fun calculate_required_fuel(mass int) int {
  return math.Floor(mass/3) - 2
}
