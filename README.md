# PintOS

Cristina Estefania Villagran Marroquin 17005199<br>
Fredy Anibal Marroquin Palencia &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;17001575<br>

### Fase 1
pass tests/threads/alarm-single<br>
pass tests/threads/alarm-multiple<br>
pass tests/threads/alarm-simultaneous<br>
pass tests/threads/alarm-priority<br>
pass tests/threads/alarm-zero<br>
pass tests/threads/alarm-negative<br>
pass tests/threads/priority-change<br>
pass tests/threads/priority-donate-one<br>
pass tests/threads/priority-donate-multiple<br>
pass tests/threads/priority-donate-multiple2<br>
FAIL tests/threads/priority-donate-nest<br>
pass tests/threads/priority-donate-sema<br>
pass tests/threads/priority-donate-lower<br>
pass tests/threads/priority-fifo<br>
pass tests/threads/priority-preempt<br>
pass tests/threads/priority-sema<br>
pass tests/threads/priority-condvar<br>
FAIL tests/threads/priority-donate-chain<br>
FAIL tests/threads/mlfqs-load-1<br>
FAIL tests/threads/mlfqs-load-60<br>
FAIL tests/threads/mlfqs-load-avg<br>
FAIL tests/threads/mlfqs-recent-1<br>
pass tests/threads/mlfqs-fair-2<br>
pass tests/threads/mlfqs-fair-20<br>
FAIL tests/threads/mlfqs-nice-2<br>
FAIL tests/threads/mlfqs-nice-10<br>
FAIL tests/threads/mlfqs-block<br>
***9 of 27 tests failed.***

### Fase 2
pass tests/userprog/args-none<br>
pass tests/userprog/args-single<br>
pass tests/userprog/args-multiple<br>
pass tests/userprog/args-many<br>
pass tests/userprog/args-dbl-space<br>
pass tests/userprog/sc-bad-sp<br>
pass tests/userprog/sc-bad-arg<br>
pass tests/userprog/sc-boundary<br>
pass tests/userprog/sc-boundary-2<br>
pass tests/userprog/sc-boundary-3<br>
pass tests/userprog/halt<br>
pass tests/userprog/exit<br>
pass tests/userprog/create-normal<br>
pass tests/userprog/create-empty<br>
pass tests/userprog/create-null<br>
pass tests/userprog/create-bad-ptr<br>
pass tests/userprog/create-long<br>
pass tests/userprog/create-exists<br>
pass tests/userprog/create-bound<br>
pass tests/userprog/open-normal<br>
pass tests/userprog/open-missing<br>
pass tests/userprog/open-boundary<br>
pass tests/userprog/open-empty<br>
pass tests/userprog/open-null<br>
pass tests/userprog/open-bad-ptr<br>
pass tests/userprog/open-twice<br>
pass tests/userprog/close-normal<br>
pass tests/userprog/close-twice<br>
pass tests/userprog/close-stdin<br>
pass tests/userprog/close-stdout<br>
pass tests/userprog/close-bad-fd<br>
pass tests/userprog/read-normal<br>
pass tests/userprog/read-bad-ptr<br>
pass tests/userprog/read-boundary<br>
pass tests/userprog/read-zero<br>
pass tests/userprog/read-stdout<br>
pass tests/userprog/read-bad-fd<br>
pass tests/userprog/write-normal<br>
pass tests/userprog/write-bad-ptr<br>
pass tests/userprog/write-boundary<br>
pass tests/userprog/write-zero<br>
pass tests/userprog/write-stdin<br>
pass tests/userprog/write-bad-fd<br>
pass tests/userprog/exec-once<br>
pass tests/userprog/exec-arg<br>
pass tests/userprog/exec-bound<br>
pass tests/userprog/exec-bound-2<br>
pass tests/userprog/exec-bound-3<br>
pass tests/userprog/exec-multiple<br>
pass tests/userprog/exec-missing<br>
pass tests/userprog/exec-bad-ptr<br>
pass tests/userprog/wait-simple<br>
pass tests/userprog/wait-twice<br>
pass tests/userprog/wait-killed<br>
pass tests/userprog/wait-bad-pid<br>
pass tests/userprog/multi-recurse<br>
pass tests/userprog/multi-child-fd<br>
pass tests/userprog/rox-simple<br>
pass tests/userprog/rox-child<br>
pass tests/userprog/rox-multichild<br>
pass tests/userprog/bad-read<br>
pass tests/userprog/bad-write<br>
pass tests/userprog/bad-read2<br>
pass tests/userprog/bad-write2<br>
pass tests/userprog/bad-jump<br>
pass tests/userprog/bad-jump2<br>
FAIL tests/userprog/no-vm/multi-oom<br>
pass tests/filesys/base/lg-create<br>
pass tests/filesys/base/lg-full<br>
pass tests/filesys/base/lg-random<br>
pass tests/filesys/base/lg-seq-block<br>
pass tests/filesys/base/lg-seq-random<br>
pass tests/filesys/base/sm-create<br>
pass tests/filesys/base/sm-full<br>
pass tests/filesys/base/sm-random<br>
pass tests/filesys/base/sm-seq-block<br>
pass tests/filesys/base/sm-seq-random<br>
FAIL tests/filesys/base/syn-read<br>
pass tests/filesys/base/syn-remove<br>
FAIL tests/filesys/base/syn-write<br>
***3 of 80 tests failed.***

### Fase 3
pass tests/userprog/args-none<br>
pass tests/userprog/args-single<br>
pass tests/userprog/args-multiple<br>
pass tests/userprog/args-many<br>
pass tests/userprog/args-dbl-space<br>
pass tests/userprog/sc-bad-sp<br>
pass tests/userprog/sc-bad-arg<br>
pass tests/userprog/sc-boundary<br>
pass tests/userprog/sc-boundary-2<br>
pass tests/userprog/sc-boundary-3<br>
pass tests/userprog/halt<br>
pass tests/userprog/exit<br>
pass tests/userprog/create-normal<br>
pass tests/userprog/create-empty<br>
pass tests/userprog/create-null<br>
pass tests/userprog/create-bad-ptr<br>
pass tests/userprog/create-long<br>
pass tests/userprog/create-exists<br>
pass tests/userprog/create-bound<br>
pass tests/userprog/open-normal<br>
pass tests/userprog/open-missing<br>
pass tests/userprog/open-boundary<br>
pass tests/userprog/open-empty<br>
pass tests/userprog/open-null<br>
pass tests/userprog/open-bad-ptr<br>
pass tests/userprog/open-twice<br>
pass tests/userprog/close-normal<br>
pass tests/userprog/close-twice<br>
pass tests/userprog/close-stdin<br>
pass tests/userprog/close-stdout<br>
pass tests/userprog/close-bad-fd<br>
pass tests/userprog/read-normal<br>
pass tests/userprog/read-bad-ptr<br>
pass tests/userprog/read-boundary<br>
pass tests/userprog/read-zero<br>
pass tests/userprog/read-stdout<br>
pass tests/userprog/read-bad-fd<br>
pass tests/userprog/write-normal<br>
pass tests/userprog/write-bad-ptr<br>
pass tests/userprog/write-boundary<br>
pass tests/userprog/write-zero<br>
pass tests/userprog/write-stdin<br>
pass tests/userprog/write-bad-fd<br>
pass tests/userprog/exec-once<br>
pass tests/userprog/exec-arg<br>
pass tests/userprog/exec-bound<br>
pass tests/userprog/exec-bound-2<br>
pass tests/userprog/exec-bound-3<br>
pass tests/userprog/exec-multiple<br>
pass tests/userprog/exec-missing<br>
pass tests/userprog/exec-bad-ptr<br>
pass tests/userprog/wait-simple<br>
pass tests/userprog/wait-twice<br>
pass tests/userprog/wait-killed<br>
pass tests/userprog/wait-bad-pid<br>
pass tests/userprog/multi-recurse<br>
pass tests/userprog/multi-child-fd<br>
pass tests/userprog/rox-simple<br>
pass tests/userprog/rox-child<br>
pass tests/userprog/rox-multichild<br>
pass tests/userprog/bad-read<br>
pass tests/userprog/bad-write<br>
pass tests/userprog/bad-read2<br>
pass tests/userprog/bad-write2<br>
pass tests/userprog/bad-jump<br>
pass tests/userprog/bad-jump2<br>
FAIL tests/vm/pt-grow-stack<br>
FAIL tests/vm/pt-grow-pusha<br>
pass tests/vm/pt-grow-bad<br>
FAIL tests/vm/pt-big-stk-obj<br>
pass tests/vm/pt-bad-addr<br>
pass tests/vm/pt-bad-read<br>
pass tests/vm/pt-write-code<br>
pass tests/vm/pt-write-code2<br>
FAIL tests/vm/pt-grow-stk-sc<br>
FAIL tests/vm/page-linear<br>
pass tests/vm/page-parallel<br>
FAIL tests/vm/page-merge-seq<br>
FAIL tests/vm/page-merge-par<br>
FAIL tests/vm/page-merge-stk<br>
FAIL tests/vm/page-merge-mm<br>
pass tests/vm/page-shuffle<br>
FAIL tests/vm/mmap-read<br>
FAIL tests/vm/mmap-close<br>
pass tests/vm/mmap-unmap<br>
FAIL tests/vm/mmap-overlap<br>
FAIL tests/vm/mmap-twice<br>
FAIL tests/vm/mmap-write<br>
FAIL tests/vm/mmap-exit<br>
FAIL tests/vm/mmap-shuffle<br>
FAIL tests/vm/mmap-bad-fd<br>
FAIL tests/vm/mmap-clean<br>
FAIL tests/vm/mmap-inherit<br>
FAIL tests/vm/mmap-misalign<br>
FAIL tests/vm/mmap-null<br>
FAIL tests/vm/mmap-over-code<br>
FAIL tests/vm/mmap-over-data<br>
FAIL tests/vm/mmap-over-stk<br>
FAIL tests/vm/mmap-remove<br>
pass tests/vm/mmap-zero<br>
pass tests/filesys/base/lg-create<br>
pass tests/filesys/base/lg-full<br>
pass tests/filesys/base/lg-random<br>
pass tests/filesys/base/lg-seq-block<br>
pass tests/filesys/base/lg-seq-random<br>
pass tests/filesys/base/sm-create<br>
pass tests/filesys/base/sm-full<br>
pass tests/filesys/base/sm-random<br>
pass tests/filesys/base/sm-seq-block<br>
pass tests/filesys/base/sm-seq-random<br>
FAIL tests/filesys/base/syn-read<br>
pass tests/filesys/base/syn-remove<br>
FAIL tests/filesys/base/syn-write<br>
***27 of 113 tests failed.***

### Fase 4
pass tests/userprog/args-none<br>
pass tests/userprog/args-single<br>
pass tests/userprog/args-multiple<br>
pass tests/userprog/args-many<br>
pass tests/userprog/args-dbl-space<br>
pass tests/userprog/sc-bad-sp<br>
pass tests/userprog/sc-bad-arg<br>
pass tests/userprog/sc-boundary<br>
pass tests/userprog/sc-boundary-2<br>
pass tests/userprog/sc-boundary-3<br>
pass tests/userprog/halt<br>
pass tests/userprog/exit<br>
pass tests/userprog/create-normal<br>
pass tests/userprog/create-empty<br>
pass tests/userprog/create-null<br>
pass tests/userprog/create-bad-ptr<br>
pass tests/userprog/create-long<br>
pass tests/userprog/create-exists<br>
pass tests/userprog/create-bound<br>
pass tests/userprog/open-normal<br>
pass tests/userprog/open-missing<br>
pass tests/userprog/open-boundary<br>
pass tests/userprog/open-empty<br>
pass tests/userprog/open-null<br>
pass tests/userprog/open-bad-ptr<br>
pass tests/userprog/open-twice<br>
pass tests/userprog/close-normal<br>
pass tests/userprog/close-twice<br>
pass tests/userprog/close-stdin<br>
pass tests/userprog/close-stdout<br>
pass tests/userprog/close-bad-fd<br>
pass tests/userprog/read-normal<br>
pass tests/userprog/read-bad-ptr<br>
pass tests/userprog/read-boundary<br>
pass tests/userprog/read-zero<br>
pass tests/userprog/read-stdout<br>
pass tests/userprog/read-bad-fd<br>
pass tests/userprog/write-normal<br>
pass tests/userprog/write-bad-ptr<br>
pass tests/userprog/write-boundary<br>
pass tests/userprog/write-zero<br>
pass tests/userprog/write-stdin<br>
pass tests/userprog/write-bad-fd<br>
pass tests/userprog/exec-once<br>
pass tests/userprog/exec-arg<br>
pass tests/userprog/exec-bound<br>
pass tests/userprog/exec-bound-2<br>
pass tests/userprog/exec-bound-3<br>
pass tests/userprog/exec-multiple<br>
pass tests/userprog/exec-missing<br>
pass tests/userprog/exec-bad-ptr<br>
pass tests/userprog/wait-simple<br>
pass tests/userprog/wait-twice<br>
pass tests/userprog/wait-killed<br>
pass tests/userprog/wait-bad-pid<br>
pass tests/userprog/multi-recurse<br>
pass tests/userprog/multi-child-fd<br>
pass tests/userprog/rox-simple<br>
pass tests/userprog/rox-child<br>
pass tests/userprog/rox-multichild<br>
pass tests/userprog/bad-read<br>
pass tests/userprog/bad-write<br>
pass tests/userprog/bad-read2<br>
pass tests/userprog/bad-write2<br>
pass tests/userprog/bad-jump<br>
pass tests/userprog/bad-jump2<br>
pass tests/filesys/base/lg-create<br>
pass tests/filesys/base/lg-full<br>
pass tests/filesys/base/lg-random<br>
pass tests/filesys/base/lg-seq-block<br>
pass tests/filesys/base/lg-seq-random<br>
pass tests/filesys/base/sm-create<br>
pass tests/filesys/base/sm-full<br>
pass tests/filesys/base/sm-random<br>
pass tests/filesys/base/sm-seq-block<br>
pass tests/filesys/base/sm-seq-random<br>
FAIL tests/filesys/base/syn-read<br>
pass tests/filesys/base/syn-remove<br>
FAIL tests/filesys/base/syn-write<br>
FAIL tests/filesys/extended/dir-empty-name<br>
FAIL tests/filesys/extended/dir-mk-tree<br>
FAIL tests/filesys/extended/dir-mkdir<br>
FAIL tests/filesys/extended/dir-open<br>
FAIL tests/filesys/extended/dir-over-file<br>
FAIL tests/filesys/extended/dir-rm-cwd<br>
pass tests/filesys/extended/dir-rm-parent<br>
pass tests/filesys/extended/dir-rm-root<br>
FAIL tests/filesys/extended/dir-rm-tree<br>
FAIL tests/filesys/extended/dir-rmdir<br>
FAIL tests/filesys/extended/dir-under-file<br>
FAIL tests/filesys/extended/dir-vine<br>
pass tests/filesys/extended/grow-create<br>
FAIL tests/filesys/extended/grow-dir-lg<br>
FAIL tests/filesys/extended/grow-file-size<br>
FAIL tests/filesys/extended/grow-root-lg<br>
FAIL tests/filesys/extended/grow-root-sm<br>
FAIL tests/filesys/extended/grow-seq-lg<br>
FAIL tests/filesys/extended/grow-seq-sm<br>
FAIL tests/filesys/extended/grow-sparse<br>
FAIL tests/filesys/extended/grow-tell<br>
FAIL tests/filesys/extended/grow-two-files<br>
FAIL tests/filesys/extended/syn-rw<br>
FAIL tests/filesys/extended/dir-empty-name-persistence<br>
FAIL tests/filesys/extended/dir-mk-tree-persistence<br>
FAIL tests/filesys/extended/dir-mkdir-persistence<br>
FAIL tests/filesys/extended/dir-open-persistence<br>
FAIL tests/filesys/extended/dir-over-file-persistence<br>
FAIL tests/filesys/extended/dir-rm-cwd-persistence<br>
FAIL tests/filesys/extended/dir-rm-parent-persistence<br>
FAIL tests/filesys/extended/dir-rm-root-persistence<br>
FAIL tests/filesys/extended/dir-rm-tree-persistence<br>
FAIL tests/filesys/extended/dir-rmdir-persistence<br>
FAIL tests/filesys/extended/dir-under-file-persistence<br>
FAIL tests/filesys/extended/dir-vine-persistence<br>
FAIL tests/filesys/extended/grow-create-persistence<br>
FAIL tests/filesys/extended/grow-dir-lg-persistence<br>
FAIL tests/filesys/extended/grow-file-size-persistence<br>
FAIL tests/filesys/extended/grow-root-lg-persistence<br>
FAIL tests/filesys/extended/grow-root-sm-persistence<br>
FAIL tests/filesys/extended/grow-seq-lg-persistence<br>
FAIL tests/filesys/extended/grow-seq-sm-persistence<br>
FAIL tests/filesys/extended/grow-sparse-persistence<br>
FAIL tests/filesys/extended/grow-tell-persistence<br>
FAIL tests/filesys/extended/grow-two-files-persistence<br>
FAIL tests/filesys/extended/syn-rw-persistence<br>
***45 of 125 tests failed.***
