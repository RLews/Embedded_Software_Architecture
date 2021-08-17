


SUBDIRS = Appl_Interface
SUBDIRS += Env_Config
SUBDIRS += Rte_Linux
SUBDIRS += Service_Interface

.PHONY: $(SUBDIRS)

all: $(SUBDIRS)

$(SUBDIRS):
	@$(MAKE) -C $@

clean:
	rm -f *.a $(OBJS)
	for d in $(SUBDIRS) ; do $(MAKE) -C $$d clean ; done
