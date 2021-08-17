


SUBDIRS = Algor
SUBDIRS += DataStructOpt DataStructOpt/src DataStructOpt/inc
SUBDIRS += Lib
SUBDIRS += Memory

.PHONY: $(SUBDIRS)

all: $(SUBDIRS)

$(SUBDIRS):
	@$(MAKE) -C $@

clean:
	rm -f *.a $(OBJS)
	for d in $(SUBDIRS) ; do $(MAKE) -C $$d clean ; done
