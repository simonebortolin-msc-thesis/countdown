/*
 * Copyright (c), University of Bologna and ETH Zurich
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 *			* Redistributions of source code must retain the above copyright notice, this
 *				list of conditions and the following disclaimer.
 *
 *			* Redistributions in binary form must reproduce the above copyright notice,
 *				this list of conditions and the following disclaimer in the documentation
 *				and/or other materials provided with the distribution.
 *
 *			* Neither the name of the copyright holder nor the names of its
 *				contributors may be used to endorse or promote products derived from
 *				this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 * Author: Daniele Cesarini, University of Bologna
*/

#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <float.h>
#include <math.h>
#include <time.h>
#include <dirent.h>
#include <stddef.h>
#include <unistd.h>
#include <sched.h>
#include <signal.h>
#include <stdint.h>
#include <string.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/time.h>
#include <sys/types.h>
#include <sys/stat.h>

// MPI
#include <mpi.h>


#ifndef _CNTD_H_
#define	_CNTD_H_

#ifdef __INTEL_COMPILER
#pragma warning disable 1786
#else	 /// GNU build
#pragma GCC diagnostic ignored "-Wdeprecated-declarations"
#endif

// EAM configurations
#define DEFAULT_TIMEOUT 500				// 500us

#define MEM_SIZE 128
#define STRING_SIZE 128

// Constants
#define FALSE 0
#define TRUE 1

#define MIN 0
#define MAX 1

#define MPI_NONE -1
#define MPI_ALL -2
#define MPI_ALLV -3
#define MPI_ALLW -4

#define START 0
#define END 1

#define PKG 0
#define DRAM 1

#define RAPL_DOMAINS 2

#define NUM_SOCKETS 8

// Enumerator
#define FOREACH_MPI(MPI) \
	MPI(__MPI_ABORT) \
	MPI(__MPI_ACCUMULATE) \
	MPI(__MPI_ADD_ERROR_CLASS) \
	MPI(__MPI_ADD_ERROR_CODE) \
	MPI(__MPI_ADD_ERROR_STRING) \
	MPI(__MPI_ADDRESS) \
	MPI(__MPI_ALLGATHER) \
	MPI(__MPI_IALLGATHER) \
	MPI(__MPI_ALLGATHERV) \
	MPI(__MPI_IALLGATHERV) \
	MPI(__MPI_ALLOC_MEM) \
	MPI(__MPI_ALLREDUCE) \
	MPI(__MPI_IALLREDUCE) \
	MPI(__MPI_ALLTOALL) \
	MPI(__MPI_IALLTOALL) \
	MPI(__MPI_ALLTOALLV) \
	MPI(__MPI_IALLTOALLV) \
	MPI(__MPI_ALLTOALLW) \
	MPI(__MPI_IALLTOALLW) \
	MPI(__MPI_ATTR_DELETE) \
	MPI(__MPI_ATTR_GET) \
	MPI(__MPI_ATTR_PUT) \
	MPI(__MPI_BARRIER) \
	MPI(__MPI_IBARRIER) \
	MPI(__MPI_BCAST) \
	MPI(__MPI_BSEND) \
	MPI(__MPI_IBCAST) \
	MPI(__MPI_BSEND_INIT) \
	MPI(__MPI_BUFFER_ATTACH) \
	MPI(__MPI_BUFFER_DETACH) \
	MPI(__MPI_CANCEL) \
	MPI(__MPI_CART_COORDS) \
	MPI(__MPI_CART_CREATE) \
	MPI(__MPI_CART_GET) \
	MPI(__MPI_CART_MAP) \
	MPI(__MPI_CART_RANK) \
	MPI(__MPI_CART_SHIFT) \
	MPI(__MPI_CART_SUB) \
	MPI(__MPI_CARTDIM_GET) \
	MPI(__MPI_CLOSE_PORT) \
	MPI(__MPI_COMM_ACCEPT) \
	MPI(__MPI_FMPI_COMM_C2F) \
	MPI(__MPI_COMM_CALL_ERRHANDLER) \
	MPI(__MPI_COMM_COMPARE) \
	MPI(__MPI_COMM_CONNECT) \
	MPI(__MPI_COMM_CREATE_ERRHANDLER) \
	MPI(__MPI_COMM_CREATE_KEYVAL) \
	MPI(__MPI_COMM_CREATE_GROUP) \
	MPI(__MPI_COMM_CREATE) \
	MPI(__MPI_COMM_DELETE_ATTR) \
	MPI(__MPI_COMM_DISCONNECT) \
	MPI(__MPI_COMM_DUP) \
	MPI(__MPI_COMM_IDUP) \
	MPI(__MPI_COMM_DUP_WITH_INFO) \
	MPI(__MPI_COMM_F2C) \
	MPI(__MPI_COMM_FREE_KEYVAL) \
	MPI(__MPI_COMM_FREE) \
	MPI(__MPI_COMM_GET_ATTR) \
	MPI(__MPI_DIST_GRAPH_CREATE) \
	MPI(__MPI_DIST_GRAPH_CREATE_ADJACENT) \
	MPI(__MPI_DIST_GRAPH_NEIGHBORS) \
	MPI(__MPI_DIST_GRAPH_NEIGHBORS_COUNT) \
	MPI(__MPI_COMM_GET_ERRHANDLER) \
	MPI(__MPI_COMM_GET_INFO) \
	MPI(__MPI_COMM_GET_NAME) \
	MPI(__MPI_COMM_GET_PARENT) \
	MPI(__MPI_COMM_GROUP) \
	MPI(__MPI_COMM_JOIN) \
	MPI(__MPI_COMM_RANK) \
	MPI(__MPI_COMM_REMOTE_GROUP) \
	MPI(__MPI_COMM_REMOTE_SIZE) \
	MPI(__MPI_COMM_SET_ATTR) \
	MPI(__MPI_COMM_SET_ERRHANDLER) \
	MPI(__MPI_COMM_SET_INFO) \
	MPI(__MPI_COMM_SET_NAME) \
	MPI(__MPI_COMM_SIZE) \
	MPI(__MPI_COMM_SPAWN) \
	MPI(__MPI_COMM_SPAWN_MULTIPLE) \
	MPI(__MPI_COMM_SPLIT) \
	MPI(__MPI_COMM_SPLIT_TYPE) \
	MPI(__MPI_COMM_TEST_INTER) \
	MPI(__MPI_COMPARE_AND_SWAP) \
	MPI(__MPI_DIMS_CREATE) \
	MPI(__MPI_FMPI_ERRHANDLER_C2F) \
	MPI(__MPI_ERRHANDLER_CREATE) \
	MPI(__MPI_ERRHANDLER_F2C) \
	MPI(__MPI_ERRHANDLER_FREE) \
	MPI(__MPI_ERRHANDLER_GET) \
	MPI(__MPI_ERRHANDLER_SET) \
	MPI(__MPI_ERROR_CLASS) \
	MPI(__MPI_ERROR_STRING) \
	MPI(__MPI_EXSCAN) \
	MPI(__MPI_FETCH_AND_OP) \
	MPI(__MPI_IEXSCAN) \
	MPI(__MPI_FILE_C2F) \
	MPI(__MPI_FILE_F2C) \
	MPI(__MPI_FILE_CALL_ERRHANDLER) \
	MPI(__MPI_FILE_CREATE_ERRHANDLER) \
	MPI(__MPI_FILE_SET_ERRHANDLER) \
	MPI(__MPI_FILE_GET_ERRHANDLER) \
	MPI(__MPI_FILE_OPEN) \
	MPI(__MPI_FILE_CLOSE) \
	MPI(__MPI_FILE_DELETE) \
	MPI(__MPI_FILE_SET_SIZE) \
	MPI(__MPI_FILE_PREALLOCATE) \
	MPI(__MPI_FILE_GET_SIZE) \
	MPI(__MPI_FILE_GET_GROUP) \
	MPI(__MPI_FILE_GET_AMODE) \
	MPI(__MPI_FILE_SET_INFO) \
	MPI(__MPI_FILE_GET_INFO) \
	MPI(__MPI_FILE_SET_VIEW) \
	MPI(__MPI_FILE_GET_VIEW) \
	MPI(__MPI_FILE_READ_AT) \
	MPI(__MPI_FILE_READ_AT_ALL) \
	MPI(__MPI_FILE_WRITE_AT) \
	MPI(__MPI_FILE_WRITE_AT_ALL) \
	MPI(__MPI_FILE_IREAD_AT) \
	MPI(__MPI_FILE_IWRITE_AT) \
	MPI(__MPI_FILE_IREAD_AT_ALL) \
	MPI(__MPI_FILE_IWRITE_AT_ALL) \
	MPI(__MPI_FILE_READ) \
	MPI(__MPI_FILE_READ_ALL) \
	MPI(__MPI_FILE_WRITE) \
	MPI(__MPI_FILE_WRITE_ALL) \
	MPI(__MPI_FILE_IREAD) \
	MPI(__MPI_FILE_IWRITE) \
	MPI(__MPI_FILE_IREAD_ALL) \
	MPI(__MPI_FILE_IWRITE_ALL) \
	MPI(__MPI_FILE_SEEK) \
	MPI(__MPI_FILE_GET_POSITION) \
	MPI(__MPI_FILE_GET_BYTE_OFFSET) \
	MPI(__MPI_FILE_READ_SHARED) \
	MPI(__MPI_FILE_WRITE_SHARED) \
	MPI(__MPI_FILE_IREAD_SHARED) \
	MPI(__MPI_FILE_IWRITE_SHARED) \
	MPI(__MPI_FILE_READ_ORDERED) \
	MPI(__MPI_FILE_WRITE_ORDERED) \
	MPI(__MPI_FILE_SEEK_SHARED) \
	MPI(__MPI_FILE_GET_POSITION_SHARED) \
	MPI(__MPI_FILE_READ_AT_ALL_BEGIN) \
	MPI(__MPI_FILE_READ_AT_ALL_END) \
	MPI(__MPI_FILE_WRITE_AT_ALL_BEGIN) \
	MPI(__MPI_FILE_WRITE_AT_ALL_END) \
	MPI(__MPI_FILE_READ_ALL_BEGIN) \
	MPI(__MPI_FILE_READ_ALL_END) \
	MPI(__MPI_FILE_WRITE_ALL_BEGIN) \
	MPI(__MPI_FILE_WRITE_ALL_END) \
	MPI(__MPI_FILE_READ_ORDERED_BEGIN) \
	MPI(__MPI_FILE_READ_ORDERED_END) \
	MPI(__MPI_FILE_WRITE_ORDERED_BEGIN) \
	MPI(__MPI_FILE_WRITE_ORDERED_END) \
	MPI(__MPI_FILE_GET_TYPE_EXTENT) \
	MPI(__MPI_FILE_SET_ATOMICITY) \
	MPI(__MPI_FILE_GET_ATOMICITY) \
	MPI(__MPI_FILE_SYNC) \
	MPI(__MPI_FINALIZE) \
	MPI(__MPI_FINALIZED) \
	MPI(__MPI_FREE_MEM) \
	MPI(__MPI_GATHER) \
	MPI(__MPI_IGATHER) \
	MPI(__MPI_GATHERV) \
	MPI(__MPI_IGATHERV) \
	MPI(__MPI_GET_ADDRESS) \
	MPI(__MPI_GET_COUNT) \
	MPI(__MPI_GET_ELEMENTS) \
	MPI(__MPI_GET_ELEMENTS_X) \
	MPI(__MPI_GET) \
	MPI(__MPI_GET_ACCUMULATE) \
	MPI(__MPI_GET_LIBRARY_VERSION) \
	MPI(__MPI_GET_PROCESSOR_NAME) \
	MPI(__MPI_GET_VERSION) \
	MPI(__MPI_GRAPH_CREATE) \
	MPI(__MPI_GRAPH_GET) \
	MPI(__MPI_GRAPH_MAP) \
	MPI(__MPI_GRAPH_NEIGHBORS_COUNT) \
	MPI(__MPI_GRAPH_NEIGHBORS) \
	MPI(__MPI_GRAPHDIMS_GET) \
	MPI(__MPI_GREQUEST_COMPLETE) \
	MPI(__MPI_GREQUEST_START) \
	MPI(__MPI_FMPI_GROUP_C2F) \
	MPI(__MPI_GROUP_COMPARE) \
	MPI(__MPI_GROUP_DIFFERENCE) \
	MPI(__MPI_GROUP_EXCL) \
	MPI(__MPI_GROUP_F2C) \
	MPI(__MPI_GROUP_FREE) \
	MPI(__MPI_GROUP_INCL) \
	MPI(__MPI_GROUP_INTERSECTION) \
	MPI(__MPI_GROUP_RANGE_EXCL) \
	MPI(__MPI_GROUP_RANGE_INCL) \
	MPI(__MPI_GROUP_RANK) \
	MPI(__MPI_GROUP_SIZE) \
	MPI(__MPI_GROUP_TRANSLATE_RANKS) \
	MPI(__MPI_GROUP_UNION) \
	MPI(__MPI_IBSEND) \
	MPI(__MPI_IMPROBE) \
	MPI(__MPI_IMRECV) \
	MPI(__MPI_FMPI_INFO_C2F) \
	MPI(__MPI_INFO_CREATE) \
	MPI(__MPI_INFO_DELETE) \
	MPI(__MPI_INFO_DUP) \
	MPI(__MPI_INFO_F2C) \
	MPI(__MPI_INFO_FREE) \
	MPI(__MPI_INFO_GET) \
	MPI(__MPI_INFO_GET_NKEYS) \
	MPI(__MPI_INFO_GET_NTHKEY) \
	MPI(__MPI_INFO_GET_VALUELEN) \
	MPI(__MPI_INFO_SET) \
	MPI(__MPI_INIT) \
	MPI(__MPI_INITIALIZED) \
	MPI(__MPI_INIT_THREAD) \
	MPI(__MPI_INTERCOMM_CREATE) \
	MPI(__MPI_INTERCOMM_MERGE) \
	MPI(__MPI_IPROBE) \
	MPI(__MPI_IRECV) \
	MPI(__MPI_IRSEND) \
	MPI(__MPI_ISEND) \
	MPI(__MPI_ISSEND) \
	MPI(__MPI_IS_THREAD_MAIN) \
	MPI(__MPI_KEYVAL_CREATE) \
	MPI(__MPI_KEYVAL_FREE) \
	MPI(__MPI_LOOKUP_NAME) \
	MPI(__MPI_FMPI_MESSAGE_C2F) \
	MPI(__MPI_MESSAGE_F2C) \
	MPI(__MPI_MPROBE) \
	MPI(__MPI_MRECV) \
	MPI(__MPI_NEIGHBOR_ALLGATHER) \
	MPI(__MPI_INEIGHBOR_ALLGATHER) \
	MPI(__MPI_NEIGHBOR_ALLGATHERV) \
	MPI(__MPI_INEIGHBOR_ALLGATHERV) \
	MPI(__MPI_NEIGHBOR_ALLTOALL) \
	MPI(__MPI_INEIGHBOR_ALLTOALL) \
	MPI(__MPI_NEIGHBOR_ALLTOALLV) \
	MPI(__MPI_INEIGHBOR_ALLTOALLV) \
	MPI(__MPI_NEIGHBOR_ALLTOALLW) \
	MPI(__MPI_INEIGHBOR_ALLTOALLW) \
	MPI(__MPI_FMPI_OP_C2F) \
	MPI(__MPI_OP_COMMUTATIVE) \
	MPI(__MPI_OP_CREATE) \
	MPI(__MPI_OPEN_PORT) \
	MPI(__MPI_OP_F2C) \
	MPI(__MPI_OP_FREE) \
	MPI(__MPI_PACK_EXTERNAL) \
	MPI(__MPI_PACK_EXTERNAL_SIZE) \
	MPI(__MPI_PACK) \
	MPI(__MPI_PACK_SIZE) \
	MPI(__MPI_PCONTROL) \
	MPI(__MPI_PROBE) \
	MPI(__MPI_PUBLISH_NAME) \
	MPI(__MPI_PUT) \
	MPI(__MPI_QUERY_THREAD) \
	MPI(__MPI_RACCUMULATE) \
	MPI(__MPI_RECV_INIT) \
	MPI(__MPI_RECV) \
	MPI(__MPI_REDUCE) \
	MPI(__MPI_IREDUCE) \
	MPI(__MPI_REDUCE_LOCAL) \
	MPI(__MPI_REDUCE_SCATTER) \
	MPI(__MPI_IREDUCE_SCATTER) \
	MPI(__MPI_REDUCE_SCATTER_BLOCK) \
	MPI(__MPI_IREDUCE_SCATTER_BLOCK) \
	MPI(__MPI_REGISTER_DATAREP) \
	MPI(__MPI_FMPI_REQUEST_C2F) \
	MPI(__MPI_REQUEST_F2C) \
	MPI(__MPI_REQUEST_FREE) \
	MPI(__MPI_REQUEST_GET_STATUS) \
	MPI(__MPI_RGET) \
	MPI(__MPI_RGET_ACCUMULATE) \
	MPI(__MPI_RPUT) \
	MPI(__MPI_RSEND) \
	MPI(__MPI_RSEND_INIT) \
	MPI(__MPI_SCAN) \
	MPI(__MPI_ISCAN) \
	MPI(__MPI_SCATTER) \
	MPI(__MPI_ISCATTER) \
	MPI(__MPI_SCATTERV) \
	MPI(__MPI_ISCATTERV) \
	MPI(__MPI_SEND_INIT) \
	MPI(__MPI_SEND) \
	MPI(__MPI_SENDRECV) \
	MPI(__MPI_SENDRECV_REPLACE) \
	MPI(__MPI_SSEND_INIT) \
	MPI(__MPI_SSEND) \
	MPI(__MPI_START) \
	MPI(__MPI_STARTALL) \
	MPI(__MPI_STATUS_C2F) \
	MPI(__MPI_STATUS_F2C) \
	MPI(__MPI_STATUS_SET_CANCELLED) \
	MPI(__MPI_STATUS_SET_ELEMENTS) \
	MPI(__MPI_STATUS_SET_ELEMENTS_X) \
	MPI(__MPI_TESTALL) \
	MPI(__MPI_TESTANY) \
	MPI(__MPI_TEST) \
	MPI(__MPI_TEST_CANCELLED) \
	MPI(__MPI_TESTSOME) \
	MPI(__MPI_TOPO_TEST) \
	MPI(__MPI_FMPI_TYPE_C2F) \
	MPI(__MPI_TYPE_COMMIT) \
	MPI(__MPI_TYPE_CONTIGUOUS) \
	MPI(__MPI_TYPE_CREATE_DARRAY) \
	MPI(__MPI_TYPE_CREATE_F90_COMPLEX) \
	MPI(__MPI_TYPE_CREATE_F90_INTEGER) \
	MPI(__MPI_TYPE_CREATE_F90_REAL) \
	MPI(__MPI_TYPE_CREATE_HINDEXED_BLOCK) \
	MPI(__MPI_TYPE_CREATE_HINDEXED) \
	MPI(__MPI_TYPE_CREATE_HVECTOR) \
	MPI(__MPI_TYPE_CREATE_KEYVAL) \
	MPI(__MPI_TYPE_CREATE_INDEXED_BLOCK) \
	MPI(__MPI_TYPE_CREATE_STRUCT) \
	MPI(__MPI_TYPE_CREATE_SUBARRAY) \
	MPI(__MPI_TYPE_CREATE_RESIZED) \
	MPI(__MPI_TYPE_DELETE_ATTR) \
	MPI(__MPI_TYPE_DUP) \
	MPI(__MPI_TYPE_EXTENT) \
	MPI(__MPI_TYPE_FREE) \
	MPI(__MPI_TYPE_FREE_KEYVAL) \
	MPI(__MPI_TYPE_F2C) \
	MPI(__MPI_TYPE_GET_ATTR) \
	MPI(__MPI_TYPE_GET_CONTENTS) \
	MPI(__MPI_TYPE_GET_ENVELOPE) \
	MPI(__MPI_TYPE_GET_EXTENT) \
	MPI(__MPI_TYPE_GET_EXTENT_X) \
	MPI(__MPI_TYPE_GET_NAME) \
	MPI(__MPI_TYPE_GET_TRUE_EXTENT) \
	MPI(__MPI_TYPE_GET_TRUE_EXTENT_X) \
	MPI(__MPI_TYPE_HINDEXED) \
	MPI(__MPI_TYPE_HVECTOR) \
	MPI(__MPI_TYPE_INDEXED) \
	MPI(__MPI_TYPE_LB) \
	MPI(__MPI_TYPE_MATCH_SIZE) \
	MPI(__MPI_TYPE_SET_ATTR) \
	MPI(__MPI_TYPE_SET_NAME) \
	MPI(__MPI_TYPE_SIZE) \
	MPI(__MPI_TYPE_SIZE_X) \
	MPI(__MPI_TYPE_STRUCT) \
	MPI(__MPI_TYPE_UB) \
	MPI(__MPI_TYPE_VECTOR) \
	MPI(__MPI_UNPACK) \
	MPI(__MPI_UNPUBLISH_NAME) \
	MPI(__MPI_UNPACK_EXTERNAL ) \
	MPI(__MPI_WAITALL) \
	MPI(__MPI_WAITANY) \
	MPI(__MPI_WAIT) \
	MPI(__MPI_WAITSOME) \
	MPI(__MPI_WIN_ALLOCATE) \
	MPI(__MPI_WIN_ALLOCATE_SHARED) \
	MPI(__MPI_WIN_ATTACH) \
	MPI(__MPI_FMPI_WIN_C2F) \
	MPI(__MPI_WIN_CALL_ERRHANDLER) \
	MPI(__MPI_WIN_COMPLETE) \
	MPI(__MPI_WIN_CREATE) \
	MPI(__MPI_WIN_CREATE_DYNAMIC) \
	MPI(__MPI_WIN_CREATE_ERRHANDLER) \
	MPI(__MPI_WIN_CREATE_KEYVAL) \
	MPI(__MPI_WIN_DELETE_ATTR) \
	MPI(__MPI_WIN_DETACH) \
	MPI(__MPI_WIN_F2C) \
	MPI(__MPI_WIN_FENCE) \
	MPI(__MPI_WIN_FLUSH) \
	MPI(__MPI_WIN_FLUSH_ALL) \
	MPI(__MPI_WIN_FLUSH_LOCAL) \
	MPI(__MPI_WIN_FLUSH_LOCAL_ALL) \
	MPI(__MPI_WIN_FREE) \
	MPI(__MPI_WIN_FREE_KEYVAL) \
	MPI(__MPI_WIN_GET_ATTR) \
	MPI(__MPI_WIN_GET_ERRHANDLER) \
	MPI(__MPI_WIN_GET_GROUP) \
	MPI(__MPI_WIN_GET_INFO) \
	MPI(__MPI_WIN_GET_NAME) \
	MPI(__MPI_WIN_LOCK) \
	MPI(__MPI_WIN_LOCK_ALL) \
	MPI(__MPI_WIN_POST) \
	MPI(__MPI_WIN_SET_ATTR) \
	MPI(__MPI_WIN_SET_ERRHANDLER) \
	MPI(__MPI_WIN_SET_INFO) \
	MPI(__MPI_WIN_SET_NAME) \
	MPI(__MPI_WIN_SHARED_QUERY) \
	MPI(__MPI_WIN_START) \
	MPI(__MPI_WIN_SYNC) \
	MPI(__MPI_WIN_TEST) \
	MPI(__MPI_WIN_UNLOCK) \
	MPI(__MPI_WIN_UNLOCK_ALL) \
	MPI(__MPI_WIN_WAIT) \
	MPI(__MPI_SEND__BARRIER) \
	MPI(__MPI_SSEND__BARRIER) \
	MPI(__MPI_BSEND__BARRIER) \
	MPI(__MPI_RSEND__BARRIER) \
	MPI(__MPI_RECV__BARRIER) \
	MPI(__MPI_SENDRECV__BARRIER) \
	MPI(__MPI_SENDRECV_REPLACE__BARRIER) \
	MPI(__MPI_CART_CREATE__BARRIER) \
	MPI(__MPI_COMM_CREATE__BARRIER) \
	MPI(__MPI_COMM_SPLIT__BARRIER) \
	MPI(__MPI_ALLGATHER__BARRIER) \
	MPI(__MPI_ALLGATHERV__BARRIER) \
	MPI(__MPI_ALLREDUCE__BARRIER) \
	MPI(__MPI_ALLTOALL__BARRIER) \
	MPI(__MPI_ALLTOALLV__BARRIER) \
	MPI(__MPI_ALLTOALLW__BARRIER) \
	MPI(__MPI_BCAST__BARRIER) \
	MPI(__MPI_EXSCAN__BARRIER) \
	MPI(__MPI_SCAN__BARRIER) \
	MPI(__MPI_GATHER__BARRIER) \
	MPI(__MPI_GATHERV__BARRIER) \
	MPI(__MPI_REDUCE__BARRIER) \
	MPI(__MPI_REDUCE_SCATTER__BARRIER) \
	MPI(__MPI_SCATTER__BARRIER) \
	MPI(__MPI_SCATTERV__BARRIER) \
	MPI(__MPI_NEIGHBOR_ALLGATHER__BARRIER) \
	MPI(__MPI_NEIGHBOR_ALLGATHERV__BARRIER) \
	MPI(__MPI_NEIGHBOR_ALLTOALL__BARRIER) \
	MPI(__MPI_NEIGHBOR_ALLTOALLV__BARRIER) \
	MPI(__MPI_NEIGHBOR_ALLTOALLW__BARRIER) \
	MPI(NUM_MPI_TYPE) \

#define GENERATE_ENUM(ENUM) ENUM,
#define GENERATE_STRING(STRING) #STRING,

// Generate enumerator
typedef enum MPI_Type {
	FOREACH_MPI(GENERATE_ENUM)
} MPI_Type_t;

// Generate array string of enumerator
__attribute__((unused)) static const char *mpi_type_str[] = {
	FOREACH_MPI(GENERATE_STRING)
};

// Global variables
typedef struct
{
	uint64_t timeout;
	double exe_time[2];
	int pstate[2];
	int enable_cntd;
	uint64_t energy[NUM_SOCKETS][RAPL_DOMAINS][2];
} CNTD_t;

CNTD_t *cntd;

// HEADERS
// init.c
void start_cntd();
void stop_cntd();
void call_start(MPI_Type_t mpi_type, MPI_Comm comm, int addr);
void call_end(MPI_Type_t mpi_type, MPI_Comm comm, int addr);

// eam_slack.c
void eam_slack_start_mpi(MPI_Type_t mpi_type, MPI_Comm comm, int addr);
void eam_slack_end_mpi(MPI_Type_t mpi_type, MPI_Comm comm, int addr);
void eam_slack_init();
void eam_slack_finalize();

// pm.c
void set_max_pstate();
void set_min_pstate();
void pm_init();
void pm_finalize();

// eam.c
void eam_start_mpi();
void eam_end_mpi();
void eam_init();
void eam_finalize();

// tool.c
int str_to_bool(const char str[]);
int read_str_from_file(char *filename, char *str);
double read_time();

#endif // _CNTD_H_
