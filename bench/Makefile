# -*- Makefile -*-
#
# examples:
#
# 1) Measure src/crypto_xof/shake256/amd64/ref/ for 32 bytes of output, 16KiB
#    input, 11 (default 1) x 10000 times (default = 10000), while printing std
#    dev (-DST_ON; requires RUNS > 1; also requires notrandombytes):
#
#   $ make bin/crypto_xof/shake256/amd64/ref/bench DEFINE='-DMINOUTBYTES=32 -DMAXOUTBYTES=32 -DMININBYTES=16384 -DMAXINBTYES=16384 -DRUNS=11 -DST_ON' RANDINC='../test/common/' RANDLIB='../test/common/notrandombytes.c'
#   $ ./bin/crypto_xof/shake256/amd64/ref/bench -
#
# --------------------------------------------------------------------
# implementations being excluded from benchmarks:
EXCLUDE ?= crypto_xof/shake256/amd64/spec/

# --------------------------------------------------------------------
AS      ?= as
CC      ?= clang
CFLAGS  ?= -Wall -Wno-unused-function -march=native -O3 -fomit-frame-pointer -fwrapv -fPIC -fPIE
JASMIN  ?= jasminc

# --------------------------------------------------------------------
# CI  - 0 or 1 depending if in CI or not : example : $ make ... CI=1 ...
# CID - CI DIRNAME
# CIC - CI CLEAR LOGS and ERRORS
# CIL - CI LOG stderr

CI      ?= 0
export CI


CID  =
CIC  = true 
CIL  =
CICL ?= "1"

ifeq ($(CI),1)

CID = $(@D)/.ci

CIC = (rm -f $(CID)/$(@F).*)

CIL = 2> $(CID)/$(@F).log || \
      (echo $$? | cat - $(CID)/$(@F).log > $(CID)/$(@F).error && \
       rm -f $(CID)/$(@F).log && \
       exit 127)
endif

# --------------------------------------------------------------------
BIN      ?= bin
LOGS     := libjade-logs-bench.tar.gz

SRC      := ../src
COMMON   := common

EXT      := ../ext
RANDLIB  ?= $(EXT)/randombytes/librandombytes.a
RANDINC  ?= $(EXT)/randombytes/
SSBD_DIR := $(EXT)/ssbd-tools

FILTER   ?= $(SRC)/crypto_%
JAZZ     ?= $(filter $(FILTER), $(filter-out $(addprefix $(SRC)/,$(EXCLUDE)), $(sort $(dir $(shell find $(SRC) -name '*.jazz')))))
BENCHDIR := $(subst $(SRC),$(BIN), $(JAZZ))

EXEC     := $(addsuffix bench, $(BENCHDIR))
OUT      := $(addsuffix .out, $(EXEC))

# --------------------------------------------------------------------

RDIR        = $(subst $(BIN)/,,$(@D))

OPERATION   = $(subst crypto_,,$(word 1, $(subst /, ,$(RDIR))))
OPERATION1  = $(shell echo $(OPERATION) | tr a-z A-Z)
NAMESPACE0  = $(subst crypto_$(OPERATION)_,,$(subst -,_,$(subst /,_,$(RDIR))))
NAMESPACE   = jade_$(OPERATION)_$(NAMESPACE0)
NAMESPACE1  = JADE_$(OPERATION1)_$(NAMESPACE0)

IDIR        = $(subst $(BIN),$(SRC),$(@D))
ASM         = $(IDIR)/$(OPERATION).s

MAIN        = $(COMMON)/crypto_$(OPERATION).c
DEFINE     ?=
DNAMESPACES = -DJADE_NAMESPACE=$(NAMESPACE1) -DJADE_NAMESPACE_LC=$(NAMESPACE)
INCLUDES    = -I$(IDIR)/include/ -I$(COMMON)/ -I$(RANDINC)
COMPILE     = $(CC) $(CFLAGS) -o $@ $(DEFINE) $(DNAMESPACES) $(INCLUDES) $(MAIN) $(ASM) $(RANDLIB) -lgsl $(CIL)

# --------------------------------------------------------------------
.PHONY: __phony benchs

default: benchs

benchs: $(EXEC)

$(EXEC):

# --------------------------------------------------------------------
include Makefile.partial_implementations

%/bench: $(RANDLIB) __phony | %/ %/$(CID)
	$(MAKE) -C $(IDIR) || true
	$(CIC)
	$(COMPILE) || true

$(RANDLIB):
	$(MAKE) -C $(@D)

# --------------------------------------------------------------------

$(BENCHDIR): ; @mkdir -p $@
ifeq ($(CI),1)
.PRECIOUS: %/$(CID)
%/$(CID): ; @mkdir -p $@
endif

# --------------------------------------------------------------------

run: $(OUT)

.NOTPARALLEL: $(OUT)
$(OUT):
%.out: %
	$(CIC)
	(cd $(dir $*) && ./bench > bench.out) $(CIL) || true

# --------------------------------------------------------------------
.PHONY: ssbd-tools
ssbd-tools:
	make -C $(SSBD_DIR)

# --------------------------------------------------------------------
ifeq ($(CI),1)

.PHONY: reporter $(LOGS)

reporter:
	$(MAKE) reporter_compilation
	$(MAKE) reporter_execution
	$(MAKE) $(LOGS)

reporter_compilation:
	./../scripts/ci/reporter/jlog "Compilation status" bench/$(BIN) bench $(CICL)

reporter_execution:
	./../scripts/ci/reporter/jlog "Execution status" bench/$(BIN) bench.out $(CICL)

ERR := $(shell test -d $(BIN) && find $(BIN) -name '*.error')
CIR := $(shell test -d $(BIN) && find $(BIN) -name '*.log') $(ERR)

$(LOGS):
	@$(JASMIN) -version > notes
ifeq ($(words $(CIR)),0)
	@echo "good job." >> notes
	@tar -zcvf $@ notes
else
	@tar -zcvf $@ notes $(CIR)
endif
	@rm notes

err:
ifneq ($(words $(ERR)),0)
	$(error $(ERR))
endif

endif

# --------------------------------------------------------------------
clean:
	rm -fr $(BIN) $(LOGS)

distclean: clean
	$(MAKE) -C $(SRC) distclean

