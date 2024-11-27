from epcore import ep
from epcore.io import io_event
from . import keycodes as kc
from typing import Callable, cast


editor: ep = None # type: ignore


def interactive(prompt: bool = False, keys: bool = False):
     def _interactive(f):
        setattr(f, "__ep_keys", keys)
        setattr(f, "__ep_prompt", prompt)
        
        return f

     return _interactive


@interactive(keys=True)
def self_insert(keys: str, **args):
    editor.current_buffer().insert_at_point(keys)
    editor.current_buffer().get_cursor().right(len(keys))


def insert_tab():
    editor.current_buffer().insert_at_point("    ")
    editor.current_buffer().get_cursor().right(4)

try:
    editor = ep()
    command_vector: dict[int, Callable] = {}
    for i in range(127):
        command_vector[i] = self_insert

    command_vector[ord('q')] = exit
    command_vector[kc.ch_max + kc.KEY_TAB] = insert_tab

    command_vector[kc.ch_max + kc.KEY_ARROW_UP] = lambda: editor.current_buffer().get_cursor().up(1)
    command_vector[kc.ch_max + kc.KEY_ARROW_DOWN] = lambda: editor.current_buffer().get_cursor().down(1)
    command_vector[kc.ch_max + kc.KEY_ARROW_LEFT] = lambda: editor.current_buffer().get_cursor().left(1)
    command_vector[kc.ch_max + kc.KEY_ARROW_RIGHT] = lambda: editor.current_buffer().get_cursor().right(1)

except Exception as e:
    if editor is not None:
        del editor
    print(" -- exception thrown during init phase --")
    print(e)
    input(" -- press any key to exit --")
    exit(1)


def handle_io(event: io_event):
    cmd = command_vector.get(event.get_value(), None)

    if cmd is not None:
        if hasattr(cmd, "__ep_keys"):
            cmd(keys=chr(event.get_value()))
        else:
            cmd()


try:
    while True:
        editor.draw()
        ev = editor.io().poll_event()
        handle_io(ev)

except Exception as e:
    del editor
    print(" -- exception thrown during runtime phase --")
    print(e)
    input("press to exit")
