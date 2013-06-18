/*
  Copyright 2013 Ondrej Kupka

  Licensed under the Apache License, Version 2.0 (the "License");
  you may not use this file except in compliance with the License.
  You may obtain a copy of the License at

    http://www.apache.org/licenses/LICENSE-2.0

  Unless required by applicable law or agreed to in writing, software
  distributed under the License is distributed on an "AS IS" BASIS,
  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  See the License for the specific language governing permissions and
  limitations under the License.
*/

#include <stdlib.h>
#include <zmq.h>

// Bridge into Go.
extern void gozmq_zc_free_fn(void *data, void *hint);

int
gozmq_zc_sendmsg(void *socket, void *data, size_t dlen, int flags, void *hint)
{
	zmq_msg_t msg;
	if (zmq_msg_init_data(&msg, data, dlen, gozmq_zc_free_fn, hint) == -1)
		return -1;

#if ZMQ_VERSION_MAJOR == 3
	if (zmq_msg_send(&msg, socket, flags) == -1)
		return -1;
#elif ZMQ_VERSION_MAJOR == 2
	if (zmq_send(socket, &msg, flags) == -1)
		return -1;
#else
#error Only libzmq 2.x and 3.x is supported.
#endif

	return 0;
}
