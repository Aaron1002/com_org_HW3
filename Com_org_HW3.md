# Exercise_1

## cachesim.h
增加 FIFO queue (二維矩陣)，第一層放 set，並將 set 裡面的 block 以 queue 的方式放在第一層的 set 裡

Fully associative queue 的部分，因為只有一個 set，所以直接在 queue 裡面放 block 即可

`icache_sim_t`: 
* `interested_in_range()`：過濾僅對 FETCH（指令擷取）感興趣 (資料型別不是 LOAD/STORE)
* `trace()`：當模擬器偵測到一筆 FETCH 存取（即指令擷取），呼叫 cache->access(addr, bytes, false)，因為指令擷取等同「讀取」，故 store=false

`dcache_sim_t`:
* `interested_in_range()`：對 LOAD（讀取）或 STORE（寫入）皆感興趣
* `trace()`：根據 type 決定呼叫 cache->access(addr,bytes, store_flag)，若 STORE，則 store_flag=true

## cachesim.cc
`init()`: 初始化 block, set、把 `fifo_queue` 製作成 cache 的架構 (把 set 放進去，並在 set 裡面放 block)

`cache_sim_t::victimize()`: 選替換的 block 時，把指定 set 裡面的 block 依照 FIFO 順序 pop 出來做為 victim，並把 block 從 queue 的後端 push 進去

`fa_cache_sim_t::victimize()`: 若 cache is full，取出先進入的 block，移除其資料，並從後面 insert 回去

`checktag()`: 比對 tag，若比對中，表示 hit，回傳該 tag 位置

`clean_invalidate()`: 先將可以用的 block 搬到 cache，不能用的 (dirty bit = 1) store 到 memory

`print_stats()`: 計算 miss rate

1. `init()` 初始化
2. `access()` 存取 cache
* 若呼叫 `check_tag()` 後 hit，若要做 write operation，則加上 dirty bit，作為後來的比較，then return
* 若 miss，選擇 victim
* 若 dirty bit & valid bit 同時為 1，則做 writeback (有效存取且被修改過才需要寫到 memory)
* 由 `miss_handler` 去存取下層 cache (呼叫 `access()`)

# Exercise_2-1

## Design philosophy:
按照上課講義的 Tiling 部分，以不改變原本執行順序的情況下，只改變 block size

依照原本未改善的程式的順序，做 block 的移動 (一次移動 8 格)

## 例外處理
以 8x8 block 為基礎，若最後剩餘的數量不到 8x8，則只處理剩餘 size `((v + 8 < n) ? (v + 8) : n)`

# Exercise_2-2
以線性代數裡，矩陣運算的技巧，一行一行且左到右算出乘法的結果 (三個矩陣的 block 皆遵循相同順序移動)

![105274_0](https://hackmd.io/_uploads/S19z7Kcfgx.jpg)
