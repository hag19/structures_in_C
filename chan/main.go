package main

func main() {
	ch := make(chan int)
	go func() {

		for i := 0; i < len(ch); i++ {
			_ = <-ch
		}
	}()

	ch <- 1
	ch <- 2
	ch <- 3
	close(ch)
}
