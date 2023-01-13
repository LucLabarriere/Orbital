let s:cpo_save=&cpo
set cpo&vim
cnoremap <silent> <Plug>(TelescopeFuzzyCommandSearch) e "lua require('telescope.builtin').command_history { default_text = [=[" . escape(getcmdline(), '"') . "]=] }"
noremap! <silent> <Plug>luasnip-expand-repeat <Cmd>lua require'luasnip'.expand_repeat()
noremap! <silent> <Plug>luasnip-delete-check <Cmd>lua require'luasnip'.unlink_current_if_deleted()
inoremap <silent> <Plug>luasnip-jump-prev <Cmd>lua require'luasnip'.jump(-1)
inoremap <silent> <Plug>luasnip-jump-next <Cmd>lua require'luasnip'.jump(1)
inoremap <silent> <Plug>luasnip-prev-choice <Cmd>lua require'luasnip'.change_choice(-1)
inoremap <silent> <Plug>luasnip-next-choice <Cmd>lua require'luasnip'.change_choice(1)
inoremap <silent> <Plug>luasnip-expand-snippet <Cmd>lua require'luasnip'.expand()
inoremap <silent> <Plug>luasnip-expand-or-jump <Cmd>lua require'luasnip'.expand_or_jump()
imap <C-G>S <Plug>ISurround
imap <C-G>s <Plug>Isurround
imap <C-S> <Plug>Isurround
inoremap <silent> <C-C> 
inoremap <C-W> u
inoremap <C-U> u
nnoremap <silent>  ggVG
nnoremap <silent>  :ClangdSwitchSourceHeader
nnoremap <silent>  <C-6>
nnoremap <silent>  <Nop>
nnoremap <silent>  :NvimTreeClose | Telescope find_files
nnoremap <silent>  :bd
tnoremap <silent>  
nnoremap <silent>  fuz :Telescope current_buffer_fuzzy_find
nnoremap <silent>  fix :lua vim.lsp.buf.code_action()
nnoremap <silent>  hel :Telescope man_pages
nnoremap <silent>  cmd :Telescope command_history
nnoremap <silent>  gre :Telescope live_grep
nnoremap <silent>  bd :%bd
nnoremap <silent>  cbr :term cbr C:\Users\lucla\Work\Programmes\OrbitalCR>
nnoremap <silent>  br :term br C:\Users\lucla\Work\Programmes\Orbital
nnoremap <silent>  cb :term cb C:\Users\lucla\Work\Programmes\Orbital
nnoremap <silent>  rr :term rr C:\Users\lucla\Work\Programmes\Orbital
nnoremap <silent>  bb :term bb C:\Users\lucla\Work\Programmes\Orbital
nnoremap <silent>  cc :term conf C:\Users\lucla\Work\Programmes\Orbital
nnoremap <silent>  bt :term bt C:\Users\lucla\Work\Programmes\Orbital
nnoremap <silent>  tt :term tt C:\Users\lucla\Work\Programmes\Orbital
nnoremap <silent>  neoc :Neogen class
nnoremap <silent>  neof :Neogen func
nnoremap <silent>  h :Glow
nnoremap <silent>  e :NvimTreeToggle
noremap <silent>   <Nop>
xnoremap # y?\V"
omap <silent> % <Plug>(MatchitOperationForward)
xmap <silent> % <Plug>(MatchitVisualForward)
nmap <silent> % <Plug>(MatchitNormalForward)
nnoremap & :&&
xnoremap * y/\V"
vnoremap <silent> < <gv
vnoremap <silent> > >gv
xmap S <Plug>VSurround
nnoremap <silent> T :ToggleTerm
nnoremap Y y$
omap <silent> [% <Plug>(MatchitOperationMultiBackward)
xmap <silent> [% <Plug>(MatchitVisualMultiBackward)
nmap <silent> [% <Plug>(MatchitNormalMultiBackward)
omap <silent> ]% <Plug>(MatchitOperationMultiForward)
xmap <silent> ]% <Plug>(MatchitVisualMultiForward)
nmap <silent> ]% <Plug>(MatchitNormalMultiForward)
xmap a% <Plug>(MatchitVisualTextObject)
nmap cS <Plug>CSurround
nmap cs <Plug>Csurround
nmap ds <Plug>Dsurround
xmap gx <Plug>NetrwBrowseXVis
nmap gx <Plug>NetrwBrowseX
omap <silent> g% <Plug>(MatchitOperationBackward)
xmap <silent> g% <Plug>(MatchitVisualBackward)
nmap <silent> g% <Plug>(MatchitNormalBackward)
xmap gS <Plug>VgSurround
nmap ySS <Plug>YSsurround
nmap ySs <Plug>YSsurround
nmap yss <Plug>Yssurround
nmap yS <Plug>YSurround
nmap ys <Plug>Ysurround
nnoremap <silent> <C-M> :NvimTreeClose | Telescope buffers
nnoremap <silent> <C-P> :NvimTreeClose | Telescope find_files
xnoremap <silent> <Plug>NetrwBrowseXVis :call netrw#BrowseXVis()
nnoremap <silent> <Plug>NetrwBrowseX :call netrw#BrowseX(netrw#GX(),netrw#CheckIfRemote(netrw#GX()))
xmap <silent> <Plug>(MatchitVisualTextObject) <Plug>(MatchitVisualMultiBackward)o<Plug>(MatchitVisualMultiForward)
onoremap <silent> <Plug>(MatchitOperationMultiForward) :call matchit#MultiMatch("W",  "o")
onoremap <silent> <Plug>(MatchitOperationMultiBackward) :call matchit#MultiMatch("bW", "o")
xnoremap <silent> <Plug>(MatchitVisualMultiForward) :call matchit#MultiMatch("W",  "n")m'gv``
xnoremap <silent> <Plug>(MatchitVisualMultiBackward) :call matchit#MultiMatch("bW", "n")m'gv``
nnoremap <silent> <Plug>(MatchitNormalMultiForward) :call matchit#MultiMatch("W",  "n")
nnoremap <silent> <Plug>(MatchitNormalMultiBackward) :call matchit#MultiMatch("bW", "n")
onoremap <silent> <Plug>(MatchitOperationBackward) :call matchit#Match_wrapper('',0,'o')
onoremap <silent> <Plug>(MatchitOperationForward) :call matchit#Match_wrapper('',1,'o')
xnoremap <silent> <Plug>(MatchitVisualBackward) :call matchit#Match_wrapper('',0,'v')m'gv``
xnoremap <silent> <Plug>(MatchitVisualForward) :call matchit#Match_wrapper('',1,'v'):if col("''") != col("$") | exe ":normal! m'" | endifgv``
nnoremap <silent> <Plug>(MatchitNormalBackward) :call matchit#Match_wrapper('',0,'n')
nnoremap <silent> <Plug>(MatchitNormalForward) :call matchit#Match_wrapper('',1,'n')
snoremap <silent> <Plug>luasnip-jump-prev <Cmd>lua require'luasnip'.jump(-1)
snoremap <silent> <Plug>luasnip-jump-next <Cmd>lua require'luasnip'.jump(1)
snoremap <silent> <Plug>luasnip-prev-choice <Cmd>lua require'luasnip'.change_choice(-1)
snoremap <silent> <Plug>luasnip-next-choice <Cmd>lua require'luasnip'.change_choice(1)
snoremap <silent> <Plug>luasnip-expand-snippet <Cmd>lua require'luasnip'.expand()
snoremap <silent> <Plug>luasnip-expand-or-jump <Cmd>lua require'luasnip'.expand_or_jump()
noremap <silent> <Plug>luasnip-expand-repeat <Cmd>lua require'luasnip'.expand_repeat()
noremap <silent> <Plug>luasnip-delete-check <Cmd>lua require'luasnip'.unlink_current_if_deleted()
nnoremap <silent> <Plug>SurroundRepeat .
nnoremap <Plug>PlenaryTestFile :lua require('plenary.test_harness').test_directory(vim.fn.expand("%:p"))
nnoremap <silent> <C-K> :ClangdSwitchSourceHeader
nnoremap <silent> <F9> :call vimspector#ToggleBreakpoint()
nnoremap <silent> <F3> :VimspectorReset
nnoremap <silent> <C-A> ggVG
nnoremap <silent> <C-X> :bd
nnoremap <silent> <C-L> <C-6>
inoremap <silent>  
imap S <Plug>ISurround
imap s <Plug>Isurround
inoremap <expr>  v:lua.MPairs.completion_confirm()
imap  <Plug>Isurround
inoremap  u
inoremap  u
let &cpo=s:cpo_save
unlet s:cpo_save
set completeopt=menu,preview,menuone,noselect
set errorformat=%f:%l:%v:\ %trror:\ %m,%-G%.%#
set foldlevelstart=99
set helplang=fr
set nohlsearch
set iskeyword=@,48-57,192-255
set keymodel=startsel
set laststatus=3
set listchars=lead:·,tab:│\ 
set makeprg=
set mouse=a
set runtimepath=~\\AppData\\Local\\nvim,~\\.config\\nvim\\autoload\\plugged\\diaglist.nvim,~\\.config\\nvim\\autoload\\plugged\\vim-airline,~\\.config\\nvim\\autoload\\plugged\\vim-airline-themes,~\\.config\\nvim\\autoload\\plugged\\nvim-autopairs,~\\.config\\nvim\\autoload\\plugged\\plenary.nvim,~\\.config\\nvim\\autoload\\plugged\\telescope.nvim,~\\.config\\nvim\\autoload\\plugged\\telescope-ui-select.nvim,~\\.config\\nvim\\autoload\\plugged\\auto-save.nvim,~\\.config\\nvim\\autoload\\plugged\\nvim-treesitter,~\\.config\\nvim\\autoload\\plugged\\nvim-treesitter-textobjects,~\\.config\\nvim\\autoload\\plugged\\neogen,~\\.config\\nvim\\autoload\\plugged\\vim-glsl,~\\.config\\nvim\\autoload\\plugged\\glow.nvim,~\\.config\\nvim\\autoload\\plugged\\vimspector,~\\.config\\nvim\\autoload\\plugged\\github-nvim-theme,~\\.config\\nvim\\autoload\\plugged\\vim-code-dark,~\\.config\\nvim\\autoload\\plugged\\onedark.nvim,~\\.config\\nvim\\autoload\\plugged\\vscode.nvim,~\\.config\\nvim\\autoload\\plugged\\gruvbox.nvim,~\\.config\\nvim\\autoload\\plugged\\catppuccin,~\\.config\\nvim\\autoload\\plugged\\dracula.nvim,~\\.config\\nvim\\autoload\\plugged\\vim-surround,~\\.config\\nvim\\autoload\\plugged\\nvim-tree.lua,~\\.config\\nvim\\autoload\\plugged\\nvim-web-devicons,~\\.config\\nvim\\autoload\\plugged\\barbar.nvim,~\\.config\\nvim\\autoload\\plugged\\nvim-lspconfig,~\\.config\\nvim\\autoload\\plugged\\mason.nvim,~\\.config\\nvim\\autoload\\plugged\\mason-lspconfig.nvim,~\\.config\\nvim\\autoload\\plugged\\nvim-cmp,~\\.config\\nvim\\autoload\\plugged\\cmp-buffer,~\\.config\\nvim\\autoload\\plugged\\cmp-path,~\\.config\\nvim\\autoload\\plugged\\cmp_luasnip,~\\.config\\nvim\\autoload\\plugged\\cmp-nvim-lsp,~\\.config\\nvim\\autoload\\plugged\\cmp-nvim-lua,~\\.config\\nvim\\autoload\\plugged\\LuaSnip,~\\.config\\nvim\\autoload\\plugged\\friendly-snippets,~\\.config\\nvim\\autoload\\plugged\\lsp-zero.nvim,~\\AppData\\Local\\nvim-data\\site,C:\\tools\\neovim\\nvim-win64\\share\\nvim\\runtime,C:\\tools\\neovim\\nvim-win64\\share\\nvim\\runtime\\pack\\dist\\opt\\matchit,C:\\tools\\neovim\\nvim-win64\\lib\\nvim,~\\AppData\\Local\\nvim-data\\site/pack/*/start/*,~\\AppData\\Local\\nvim-data\\site\\after,~\\.config\\nvim\\autoload\\plugged\\vim-glsl\\after,~\\.config\\nvim\\autoload\\plugged\\catppuccin\\after,~\\.config\\nvim\\autoload\\plugged\\cmp-buffer\\after,~\\.config\\nvim\\autoload\\plugged\\cmp-path\\after,~\\.config\\nvim\\autoload\\plugged\\cmp_luasnip\\after,~\\.config\\nvim\\autoload\\plugged\\cmp-nvim-lsp\\after,~\\.config\\nvim\\autoload\\plugged\\cmp-nvim-lua\\after,~\\AppData\\Local\\nvim\\after
set scrolloff=8
set shell=pwsh
set shellcmdflag=-NoLogo\ -Command\ [Console]::InputEncoding=[Console]::OutputEncoding=[System.Text.Encoding]::UTF8;
set shellpipe=2>&1\ |\ Out-File\ -Encoding\ UTF8\ %s;\ exit\ $LastExitCode
set shellredir=-RedirectStandardOutput\ %s\ -NoNewWindow\ -Wait
set shellxquote=
set shiftwidth=4
set showtabline=2
set sidescrolloff=8
set smartcase
set smartindent
set splitright
set noswapfile
set tabline=%1@BufferlineMainClickHandler@%#BufferCurrentSign#▎\ \ \ \ %1@BufferlineMainClickHandler@%#DevIconCppCurrent#\ %1@BufferlineMainClickHandler@%#BufferCurrent#OrbitalApplication.cpp\ \ \ \ %1@BufferlineCloseClickHandler@%#BufferCurrent#\ %5@BufferlineMainClickHandler@%#BufferVisibleSign#▎\ \ \ \ %5@BufferlineMainClickHandler@%#DevIconDefaultVisible#\ %5@BufferlineMainClickHandler@%#BufferVisible#[buffer\ 5]\ \ \ \ %5@BufferlineCloseClickHandler@%#BufferVisible#\ %4@BufferlineMainClickHandler@%#BufferInactiveSign#▎\ \ \ \ %4@BufferlineMainClickHandler@%#BufferInactive#\ %4@BufferlineMainClickHandler@%#BufferInactive#OrbitalApplication.h\ \ \ \ %4@BufferlineCloseClickHandler@%#BufferInactive#\ %0@BufferlineMainClickHandler@%#BufferTabpageFill#▎%#BufferTabpageFill#
set tabstop=4
set termguicolors
set undofile
set updatetime=300
set window=29
" vim: set ft=vim :
