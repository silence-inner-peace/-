# Race conditions

Looking back at the previous exercise you could wonder what forces us to call `MPI_Wait` or `MPI_Test`. After all, if we are sure the process has been idling long enough, the receiving buffer should be filled with the data eventually. Not quite in fact. The problem lies between what the standard does in theory, and how it is implemented in practice. To convince you, here is a very simple example. Try to guess what the result should be in theory, then click the run button to see what happens (No need to modify anything from the source code, just watch the behaviour).

@[No waiting, no testing]({"stubs": ["p2p_race_conditions/no_wait.cpp"], "command": "bash p2p_race_conditions/no_wait.sh"})

As you can see, the result is not quite expected. Why does that happen ? Well it is mainly an implementation question, and the technicallity of it might be too complicated for this course, so let's just state things in a simple way : you **HAVE** to call `MPI_Wait` at some point, or `MPI_Test` until the request is processed. Such a limitation might be annoying, but that's because we have not introduced the biggest of all plagues in parallel computing : **race conditions**.

A race condition is when two process try to access some data at the same time. For instance (cf figure below), if I have two processes `P0` and `P1`. `P0` sends a non-blocking message to `P1` then starts working again on the same buffer it has just sent. `P1` only waits for the reception. Well, if the request is not processed before `P1` has actually received the data, it is possible that `P0` has already modified its buffer and the data received by `P1` might be invalid. The name race condition is now really clear : Both processing are racing for the data. If `P0` is faster then the data `P1` will receive might not be what you wanted to send it. On the other hand, if `P1` is faster, then the data received will be correct. However, since both process are running in parallel, you have absolutely no guarantee on the outcome. This is a very serious problem in every parallel program. In MPI we are spared most of the race conditions problems (compared to shared-memory parallelism where these problems are omnipresent), but non-blocking communications are the exception to this.

![Race conditions](/img/p2p_race_condition.png)

One additional thing that is pictured on the image is that it does not matter if your `MPI_Irecv` is actually called after `MPI_Isend`, the request will be processed internally so even if both of your processes are ready and willing to transmit the data, you never choose when the non-blockin communication is going to happen. Also note that what is depicted is really schematical to help you understand what is happening in the worst case.

It is imperative to understand the semantic behind non-blocking communications in MPI. A non-blocking communication is an agreement both of your process are making, to avoid reading or writing the communication buffers before the request is fulfilled. The only way to make sure the request has been completed is to use `MPI_Wait` or `MPI_Test`. Only after can your processes use the communication buffers. Hence, a program using non-blocking sends or receives will always have to call `MPI_Wait` eventually before reading or writing to the comm-buffer.

That also encourages your processes to separate the communication buffers from the data structures of your program.

## Take-away point :

`MPI_Isend` and `MPI_Irecv` **MUST** be followed at some point by `MPI_Test` and `MPI_Wait`. The process sending should never **write** in the buffer until the request has been completed. On the other hand, the process receiving should never **read** in the buffer before the request has been completed. And the only way to know if a request is completed, is to call `MPI_Wait` and `MPI_Test`.