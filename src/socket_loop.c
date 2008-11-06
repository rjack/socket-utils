int
socket_loop (const struct chan *chan[], const size_t nchan,
		nearest_tout, is_done)
{
	int i;
	int maxfd;

	fd_set rd_set;
	fd_set wr_set;

	struct timeval tmout;
	int use_tmout;

	while (!is_done ()) {

		manage_buffers (chan);

		do {
			maxfd = -1;
			FD_ZERO (&rd_set);
			FD_ZERO (&wr_set);

			use_tmout = nearest_tmout (&tmout, chan);

			maxfd = set_file_descriptors (chan, rd_set, wr_set);

			nready = select (maxfd + 1,
			                 &rd_set, &wr_set, NULL,
			                 (use_tmout ? &tmout : NULL));

		} while (nready == -1 && errno == EINTR);
	}
}
