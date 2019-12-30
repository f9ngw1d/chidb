/*
 *  chidb - a didactic relational database management system
 *
 *  Database Machine operations.
 *
 */

/*
 *  Copyright (c) 2009-2015, The University of Chicago
 *  All rights reserved.
 *
 *  Redistribution and use in source and binary forms, with or withsend
 *  modification, are permitted provided that the following conditions are met:
 *
 *  - Redistributions of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer.
 *
 *  - Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 *
 *  - Neither the name of The University of Chicago nor the names of its
 *    contributors may be used to endorse or promote products derived from this
 *    software withsend specific prior written permission.
 *
 *  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 *  AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 *  IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 *  ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
 *  LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 *  CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 *  SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 *  INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 *  CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 *  ARISING IN ANY WAY send OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 *  POSSIBILITY OF SUCH DAMAGE.
 *
 */


#include "dbm.h"
#include "btree.h"
#include "record.h"


/* Function pointer for dispatch table */
typedef int (*handler_function)(chidb_stmt *stmt, chidb_dbm_op_t *op);

/* Single entry in the instruction dispatch table */
struct handler_entry
{
    opcode_t opcode;
    handler_function func;
};

/* This generates all the instruction handler prototypes. It expands to:
 *
 * int chidb_dbm_op_OpenRead(chidb_stmt *stmt, chidb_dbm_op_t *op);
 * int chidb_dbm_op_OpenWrite(chidb_stmt *stmt, chidb_dbm_op_t *op);
 * ...
 * int chidb_dbm_op_Halt(chidb_stmt *stmt, chidb_dbm_op_t *op);
 */
#define HANDLER_PROTOTYPE(OP) int chidb_dbm_op_## OP (chidb_stmt *stmt, chidb_dbm_op_t *op);
FOREACH_OP(HANDLER_PROTOTYPE)


/* Ladies and gentlemen, the dispatch table. */
#define HANDLER_ENTRY(OP) { Op_ ## OP, chidb_dbm_op_## OP},

struct handler_entry dbm_handlers[] =
{
    FOREACH_OP(HANDLER_ENTRY)
};

int chidb_dbm_op_handle (chidb_stmt *stmt, chidb_dbm_op_t *op)
{
    return dbm_handlers[op->opcode].func(stmt, op);
}
/*** TOOL FUNCTIONS ***/
int realloc_cur(chidb_stmt *stmt, uint32_t size);
int realloc_reg(chidb_stmt *stmt, uint32_t size);

int chidb_dbm_op_WriteReg(chidb_stmt *stmt, int regNo, int reg_type, void *data)
{
    int rt;
    if (IS_VALID_REGISTER(stmt, regNo) && regNo > stmt->nReg)
        if(rt = realloc_reg(stmt, regNo)) {
            return rt;
        }

    chidb_dbm_register_t *reg = &(stmt->reg[regNo]);
    reg->type = reg_type;

    if (reg_type == REG_INT32)
        reg->value.i = *((int32_t *) data);
    else if (reg_type == REG_STRING)
        reg->value.s = (char *) data;

    return CHIDB_OK;
}

/*** INSTRUCTION HANDLER IMPLEMENTATIONS ***/


int chidb_dbm_op_Noop (chidb_stmt *stmt, chidb_dbm_op_t *op)
{
    return CHIDB_OK;
}


int chidb_dbm_op_OpenRead (chidb_stmt *stmt, chidb_dbm_op_t *op)
{
    /* Your code goes here */

    return CHIDB_OK;
}


int chidb_dbm_op_OpenWrite (chidb_stmt *stmt, chidb_dbm_op_t *op)
{
    /* Your code goes here */

    return CHIDB_OK;
}


int chidb_dbm_op_Close (chidb_stmt *stmt, chidb_dbm_op_t *op)
{
    /* Your code goes here */

    return CHIDB_OK;
}


int chidb_dbm_op_Rewind (chidb_stmt *stmt, chidb_dbm_op_t *op)
{
    /* Your code goes here */

    return CHIDB_OK;
}


int chidb_dbm_op_Next (chidb_stmt *stmt, chidb_dbm_op_t *op)
{
    /* Your code goes here */

    return CHIDB_OK;
}


int chidb_dbm_op_Prev (chidb_stmt *stmt, chidb_dbm_op_t *op)
{
    /* Your code goes here */

    return CHIDB_OK;
}


int chidb_dbm_op_Seek (chidb_stmt *stmt, chidb_dbm_op_t *op)
{
    /* Your code goes here */

    return CHIDB_OK;
}


int chidb_dbm_op_SeekGt (chidb_stmt *stmt, chidb_dbm_op_t *op)
{
    /* Your code goes here */

    return CHIDB_OK;
}


int chidb_dbm_op_SeekGe (chidb_stmt *stmt, chidb_dbm_op_t *op)
{
    /* Your code goes here */

    return CHIDB_OK;
}

int chidb_dbm_op_SeekLt (chidb_stmt *stmt, chidb_dbm_op_t *op)
{
    /* Your code goes here */

    return CHIDB_OK;
}


int chidb_dbm_op_SeekLe (chidb_stmt *stmt, chidb_dbm_op_t *op)
{
    /* Your code goes here */

    return CHIDB_OK;
}

int chidb_dbm_op_Column (chidb_stmt *stmt, chidb_dbm_op_t *op)
{
    /* Your code goes here */

    return CHIDB_OK;
}


int chidb_dbm_op_Key (chidb_stmt *stmt, chidb_dbm_op_t *op)
{
    /* Your code goes here */

    return CHIDB_OK;
}


int chidb_dbm_op_Integer (chidb_stmt *stmt, chidb_dbm_op_t *op)
{
    /* Your code goes here */
    int rt;
    if(rt = chidb_dbm_op_WriteReg(stmt, op->p2, REG_INT32, &op->p1)) {
        return rt;
    }
    return CHIDB_OK;
}


int chidb_dbm_op_String (chidb_stmt *stmt, chidb_dbm_op_t *op)
{
    /* Your code goes here */
    int rt;
    if(rt = chidb_dbm_op_WriteReg(stmt, op->p2, REG_STRING, strdup(op->p4))) {
        return rt;
    }
    return CHIDB_OK;
}


int chidb_dbm_op_Null (chidb_stmt *stmt, chidb_dbm_op_t *op)
{
    /* Your code goes here */
    int rt;
    if(rt = chidb_dbm_op_WriteReg(stmt, op->p2, REG_NULL, NULL)) {
        return rt;
    }
    return CHIDB_OK;
}


int chidb_dbm_op_ResultRow (chidb_stmt *stmt, chidb_dbm_op_t *op)
{
    /* Your code goes here */

    return CHIDB_OK;
}


int chidb_dbm_op_MakeRecord (chidb_stmt *stmt, chidb_dbm_op_t *op)
{
    /* Your code goes here */

    return CHIDB_OK;
}


int chidb_dbm_op_Insert (chidb_stmt *stmt, chidb_dbm_op_t *op)
{
    /* Your code goes here */

    return CHIDB_OK;
}


int chidb_dbm_op_Eq (chidb_stmt *stmt, chidb_dbm_op_t *op)
{
    /* Your code goes here */
    if (!IS_VALID_REGISTER(stmt, op->p1))
        return CHIDB_EVALIDEARG;
    if (!IS_VALID_REGISTER(stmt, op->p3))
        return CHIDB_EVALIDEARG;
    if (!IS_VALID_ADDRESS(stmt, op->p2))
        return CHIDB_EVALIDEARG;

    chidb_dbm_register_t *reg1 = &((stmt)->reg[op->p1]);
    chidb_dbm_register_t *reg2 = &((stmt)->reg[op->p3]);

    if(reg1->type == REG_INT32 && reg2->type == REG_INT32) {
        if(reg1->value.i == reg2->value.i) {
            stmt->pc = (uint32_t)op->p2;
        }
    }
    else if(reg1->type == REG_STRING && reg2->type == REG_STRING) {
        if(!strncmp(reg1->value.s,reg2->value.s, strlen(reg1->value.s))) {
            stmt->pc = (uint32_t)op->p2;
        }
    }
    return CHIDB_OK;
}


int chidb_dbm_op_Ne (chidb_stmt *stmt, chidb_dbm_op_t *op)
{
    /* Your code goes here */
    if (!IS_VALID_REGISTER(stmt, op->p1))
        return CHIDB_EVALIDEARG;
    if (!IS_VALID_REGISTER(stmt, op->p3))
        return CHIDB_EVALIDEARG;
    if (!IS_VALID_ADDRESS(stmt, op->p2))
        return CHIDB_EVALIDEARG;

    chidb_dbm_register_t *reg1 = &((stmt)->reg[op->p1]);
    chidb_dbm_register_t *reg2 = &((stmt)->reg[op->p3]);

    if(reg1->type == REG_INT32 && reg2->type == REG_INT32) {
        if(reg1->value.i != reg2->value.i) {
            stmt->pc = (uint32_t)op->p2;
        }
    }
    else if(reg1->type == REG_STRING && reg2->type == REG_STRING) {
        if(strncmp(reg1->value.s,reg2->value.s, strlen(reg1->value.s))) {
            stmt->pc = (uint32_t)op->p2;
        }
    }
    return CHIDB_OK;
}


int chidb_dbm_op_Lt (chidb_stmt *stmt, chidb_dbm_op_t *op)
{
    /* Your code goes here */
    if (!IS_VALID_REGISTER(stmt, op->p1))
        return CHIDB_EVALIDEARG;
    if (!IS_VALID_REGISTER(stmt, op->p3))
        return CHIDB_EVALIDEARG;
    if (!IS_VALID_ADDRESS(stmt, op->p2))
        return CHIDB_EVALIDEARG;

    chidb_dbm_register_t *reg1 = &((stmt)->reg[op->p1]);
    chidb_dbm_register_t *reg2 = &((stmt)->reg[op->p3]);

    if(reg1->type == REG_INT32 && reg2->type == REG_INT32) {
        if(reg1->value.i > reg2->value.i) {
            stmt->pc = (uint32_t)op->p2;
        }
    }
    else if(reg1->type == REG_STRING && reg2->type == REG_STRING) {
        if(strncmp(reg1->value.s,reg2->value.s, strlen(reg1->value.s)) > 0) {
            stmt->pc = (uint32_t)op->p2;
        }
    }
    return CHIDB_OK;
}


int chidb_dbm_op_Le (chidb_stmt *stmt, chidb_dbm_op_t *op)
{
    /* Your code goes here */
    if (!IS_VALID_REGISTER(stmt, op->p1))
        return CHIDB_EVALIDEARG;
    if (!IS_VALID_REGISTER(stmt, op->p3))
        return CHIDB_EVALIDEARG;
    if (!IS_VALID_ADDRESS(stmt, op->p2))
        return CHIDB_EVALIDEARG;

    chidb_dbm_register_t *reg1 = &((stmt)->reg[op->p1]);
    chidb_dbm_register_t *reg2 = &((stmt)->reg[op->p3]);

    if(reg1->type == REG_INT32 && reg2->type == REG_INT32) {
        if(reg1->value.i >= reg2->value.i) {
            stmt->pc = (uint32_t)op->p2;
        }
    }
    else if(reg1->type == REG_STRING && reg2->type == REG_STRING) {
        if(strncmp(reg1->value.s,reg2->value.s, strlen(reg1->value.s)) >= 0) {
            stmt->pc = (uint32_t)op->p2;
        }
    }
    return CHIDB_OK;
}


int chidb_dbm_op_Gt (chidb_stmt *stmt, chidb_dbm_op_t *op)
{
    /* Your code goes here */
    if (!IS_VALID_REGISTER(stmt, op->p1))
        return CHIDB_EVALIDEARG;
    if (!IS_VALID_REGISTER(stmt, op->p3))
        return CHIDB_EVALIDEARG;
    if (!IS_VALID_ADDRESS(stmt, op->p2))
        return CHIDB_EVALIDEARG;

    chidb_dbm_register_t *reg1 = &((stmt)->reg[op->p1]);
    chidb_dbm_register_t *reg2 = &((stmt)->reg[op->p3]);

    if(reg1->type == REG_INT32 && reg2->type == REG_INT32) {
        if(reg1->value.i < reg2->value.i) {
            stmt->pc = (uint32_t)op->p2;
        }
    }
    else if(reg1->type == REG_STRING && reg2->type == REG_STRING) {
        if(strncmp(reg1->value.s,reg2->value.s, strlen(reg1->value.s)) < 0) {
            stmt->pc = (uint32_t)op->p2;
        }
    }
    return CHIDB_OK;
}


int chidb_dbm_op_Ge (chidb_stmt *stmt, chidb_dbm_op_t *op)
{
    /* Your code goes here */
    if (!IS_VALID_REGISTER(stmt, op->p1))
        return CHIDB_EVALIDEARG;
    if (!IS_VALID_REGISTER(stmt, op->p3))
        return CHIDB_EVALIDEARG;
    if (!IS_VALID_ADDRESS(stmt, op->p2))
        return CHIDB_EVALIDEARG;

    chidb_dbm_register_t *reg1 = &((stmt)->reg[op->p1]);
    chidb_dbm_register_t *reg2 = &((stmt)->reg[op->p3]);

    if(reg1->type == REG_INT32 && reg2->type == REG_INT32) {
        if(reg1->value.i <= reg2->value.i) {
            stmt->pc = (uint32_t)op->p2;
        }
    }
    else if(reg1->type == REG_STRING && reg2->type == REG_STRING) {
        if(strncmp(reg1->value.s,reg2->value.s, strlen(reg1->value.s)) <= 0) {
            stmt->pc = (uint32_t)op->p2;
        }
    }
    return CHIDB_OK;
}


/* IdxGt p1 p2 p3 *
 *
 * p1: cursor
 * p2: jump addr
 * p3: register containing value k
 * 
 * if (idxkey at cursor p1) > k, jump
 */
int chidb_dbm_op_IdxGt (chidb_stmt *stmt, chidb_dbm_op_t *op)
{
  fprintf(stderr,"todo: chidb_dbm_op_IdxGt\n");
  exit(1);
}

/* IdxGe p1 p2 p3 *
 *
 * p1: cursor
 * p2: jump addr
 * p3: register containing value k
 * 
 * if (idxkey at cursor p1) >= k, jump
 */
int chidb_dbm_op_IdxGe (chidb_stmt *stmt, chidb_dbm_op_t *op)
{
  fprintf(stderr,"todo: chidb_dbm_op_IdxGe\n");
  exit(1);
}

/* IdxLt p1 p2 p3 *
 *
 * p1: cursor
 * p2: jump addr
 * p3: register containing value k
 * 
 * if (idxkey at cursor p1) < k, jump
 */
int chidb_dbm_op_IdxLt (chidb_stmt *stmt, chidb_dbm_op_t *op)
{
  fprintf(stderr,"todo: chidb_dbm_op_IdxLt\n");
  exit(1);
}

/* IdxLe p1 p2 p3 *
 *
 * p1: cursor
 * p2: jump addr
 * p3: register containing value k
 * 
 * if (idxkey at cursor p1) <= k, jump
 */
int chidb_dbm_op_IdxLe (chidb_stmt *stmt, chidb_dbm_op_t *op)
{
  fprintf(stderr,"todo: chidb_dbm_op_IdxLe\n");
  exit(1);
}


/* IdxPKey p1 p2 * *
 *
 * p1: cursor
 * p2: register
 *
 * store pkey from (cell at cursor p1) in (register at p2)
 */
int chidb_dbm_op_IdxPKey (chidb_stmt *stmt, chidb_dbm_op_t *op)
{
  fprintf(stderr,"todo: chidb_dbm_op_IdxKey\n");
  exit(1);
}

/* IdxInsert p1 p2 p3 *
 *
 * p1: cursor
 * p2: register containing IdxKey
 * p2: register containing PKey
 *
 * add new (IdkKey,PKey) entry in index BTree pointed at by cursor at p1
 */
int chidb_dbm_op_IdxInsert (chidb_stmt *stmt, chidb_dbm_op_t *op)
{
  fprintf(stderr,"todo: chidb_dbm_op_IdxInsert\n");
  exit(1);
}


int chidb_dbm_op_CreateTable (chidb_stmt *stmt, chidb_dbm_op_t *op)
{
    /* Your code goes here */

    return CHIDB_OK;
}


int chidb_dbm_op_CreateIndex (chidb_stmt *stmt, chidb_dbm_op_t *op)
{
    /* Your code goes here */

    return CHIDB_OK;
}


int chidb_dbm_op_Copy (chidb_stmt *stmt, chidb_dbm_op_t *op)
{
    /* Your code goes here */

    return CHIDB_OK;
}


int chidb_dbm_op_SCopy (chidb_stmt *stmt, chidb_dbm_op_t *op)
{
    /* Your code goes here */

    return CHIDB_OK;
}


int chidb_dbm_op_Halt (chidb_stmt *stmt, chidb_dbm_op_t *op)
{
    /* Your code goes here */

    return CHIDB_DONE;
}

