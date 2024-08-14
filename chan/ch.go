package main

import "fmt"

func haldon(ch chan int) {
	for v := range ch {
		fmt.Println(v)
	}
}
