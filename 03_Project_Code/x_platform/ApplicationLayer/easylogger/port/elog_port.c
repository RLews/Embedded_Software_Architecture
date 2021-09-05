/*
 * This file is part of the EasyLogger Library.
 *
 * Copyright (c) 2015, Armink, <armink.ztl@gmail.com>
 *
 * Permission is hereby granted, free of charge, to any person obtaining
 * a copy of this software and associated documentation files (the
 * 'Software'), to deal in the Software without restriction, including
 * without limitation the rights to use, copy, modify, merge, publish,
 * distribute, sublicense, and/or sell copies of the Software, and to
 * permit persons to whom the Software is furnished to do so, subject to
 * the following conditions:
 *
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED 'AS IS', WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
 * IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY
 * CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
 * TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
 * SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 *
 * Function: Portable interface for each platform.
 * Created on: 2015-04-28
 */
 
#include <elog.h>
#include "elog_if.h"
#include "elog_level_ctrl.h"

#ifdef ELOG_FILE_ENABLE
#include <elog_file.h>
#endif

/**
 * EasyLogger port initialize
 *
 * @return result
 */
ElogErrCode elog_port_init(void) {
    ElogErrCode result = ELOG_NO_ERR;

    /* add your code here */
    Elog_OutputLockInit();
    
#ifdef ELOG_FILE_ENABLE
    elog_file_init();
#endif


    return result;
}

/**
 * EasyLogger port deinitialize
 *
 */
void elog_port_deinit(void) {

    /* add your code here */
    Elog_OutputLockDeinit();
    
#ifdef ELOG_FILE_ENABLE
    Elog_FileLockDeinit();
#endif
}

/**
 * output log port interface
 *
 * @param log output of log
 * @param size log size
 */
void elog_port_output(const char *log, size_t size) {

    /* add your code here */
    printf("%.*s", (int)size, log);

#ifdef ELOG_FILE_ENABLE
    elog_file_write(log, size);
#endif
}

/**
 * output lock
 */
void elog_port_output_lock(void) {
    
    /* add your code here */
    Elog_OutputLock();
}

/**
 * output unlock
 */
void elog_port_output_unlock(void) {
    
    /* add your code here */
    Elog_OutputUnlock();
}

/**
 * get current time interface
 *
 * @return current time
 */
const char *elog_port_get_time(void) {
    
    /* add your code here */
    return Elog_GetCurrentTime();
}

/**
 * get current process name interface
 *
 * @return current process name
 */
const char *elog_port_get_p_info(void) {
    
    /* add your code here */
    return Elog_GetPid();
}

/**
 * get current thread name interface
 *
 * @return current thread name
 */
const char *elog_port_get_t_info(void) {
    
    /* add your code here */
    return Elog_GetThreadId();
}
