local servers = require 'typst-preview.servers'
local utils = require 'typst-preview.utils'

local M = {}

---Scroll debounce timer
local scroll_timer = nil
local scroll_cancelled = false

---Register event listener
---@param s Server
function M.add_listeners(s)
  servers.listen_scroll(s, function(event)
    local function editorScrollTo()
      utils.debug(event.end_.row .. ' ' .. event.end_.column)
      s.suppress = true
      local row = event.end_.row + 1
      local max_row = vim.fn.line '$'
      if row < 1 then
        row = 1
      end
      if row > max_row then
        row = max_row
      end
      local column = event.end_.column - 1
      local max_column = vim.fn.col '$' - 1
      if column < 0 then
        column = 0
      end
      if column > max_column then
        column = max_column
      end
      vim.api.nvim_win_set_cursor(0, { row, column })
      -- Cancel any existing scroll timer
      if scroll_timer then
        scroll_cancelled = true
        vim.fn.timer_stop(scroll_timer)
      end

      scroll_cancelled = false
      scroll_timer = vim.fn.timer_start(50, function()
        if not scroll_cancelled then
          s.suppress = false
        end
        scroll_timer = nil
      end)
    end

    if event.filepath ~= utils.get_buf_path(0) then
      vim.cmd('e ' .. vim.fn.fnameescape(event.filepath))
      vim.defer_fn(editorScrollTo, 100)
    else
      editorScrollTo()
    end
  end)
end

return M
