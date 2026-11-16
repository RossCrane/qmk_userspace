"""Draws docs/keymap.svg, a one-page cheat sheet of the knaughtt keymap.

The labels below are typed by hand from keymap.c. When a layer changes in
keymap.c, change the matching list here and run:  py tools/draw_keymap.py
Order of every list: row 1 left 5 + right 5, row 2, row 3, then thumbs (3 left, 2 right).
"""
import html, os

SYM = "! @ # $ % ` { } \\ ; ^ & * , . ' ( ) _ = . . . . . \" [ ] - / Esc Spc . Ent Bsp".split()
NUM = "/ 7 8 9 * . . . . . - 4 5 6 + . . . . . = 1 2 3 . . . . . . _ 0 Ent . Bsp".split()
NAV = ". PgDn Up PgUp Fast Fast PgUp Up PgDn . . Left Down Right Slow Slow Left Down Right . . . . . . MClk . . . . RClk LClk MClk RClk LClk".split()
FUN = "Boot Wipe RGB- RGB RGB+ PrSc F7 F8 F9 F12 Prev Vol- Mute Vol+ Next ScLk F4 F5 F6 F11 . . . . QWERTY Paus F1 F2 F3 F10 . Play Stop AI Play".split()
ARROWS = {"Up": "\u2191", "Down": "\u2193", "Left": "\u2190", "Right": "\u2192"}

HOLD = ["Nav", "", "", "", "Mouse", "Func", "", "", "", "Nav",
        "", "", "", "", "", "", "", "", "", "",
        "Win", "Alt", "Ctrl", "Shift", "", "", "Shift", "Ctrl", "AltGr", "2x: Game",
        "Func", "", "Sym", "Num", ""]
COLEMAK = "Q W F P B J L U Y ; A R S T G M N E I O Z X C D V K H , . / Esc Space Tab Enter Bksp".split()
QWERTY = "Q W E R T Y U I O P A S D F G H J K L ; Z X C V B N M , . / Esc Space Tab Enter Bksp".split()
GAME_MOUSE = ["Esc", "Q", "X", "E", "R", "", "", "", "", "",
              "Shift", "A", "W", "D", "F", "Scroll", "Left click", "Right click", "Middle click", "Precise",
              "Ctrl", "Z", "S", "C", "V", "", "", "", "", "",
              "1", "Space", "Tab", "", ""]
GM_HOLD = [""] * 35
GM_HOLD[15] = "hold + roll"; GM_HOLD[19] = "hold + roll"

C = {"sym": "#1a7f37", "num": "#0969da", "nav": "#bc4c00", "fun": "#8250df", "hold": "#cf222e"}
U, K = 96, 90
STAG = [26, 10, 0, 10, 20]
GAP = 150
W = 10 * U + GAP + 60
BOARD_H = 4 * U + 90

def pos(i):
    """Top-left pixel of key i inside a board."""
    if i < 30:
        r, c = divmod(i, 10)
        if c < 5:
            return 30 + c * U, r * U + STAG[c]
        return 30 + 5 * U + GAP + (c - 5) * U, r * U + STAG[9 - c]
    t = i - 30
    if t < 3:
        return 30 + (2.55 + t) * U, 3 * U + 38
    return 30 + 5 * U + GAP + (t - 3 - 0.55) * U + U * 0.5, 3 * U + 38

def t(x, y, s, size, fill="#1f2328", anchor="middle", weight="normal"):
    s = ARROWS.get(s, s)
    return f'<text x="{x:.0f}" y="{y:.0f}" font-size="{size}" fill="{fill}" text-anchor="{anchor}" font-weight="{weight}">{html.escape(s)}</text>'

def board(y0, title, sub, taps, holds, corners):
    o = [f'<g transform="translate(0,{y0})">', t(30, -34, title, 26, anchor="start", weight="bold"),
         t(30, -12, sub, 14, fill="#57606a", anchor="start")]
    for i in range(35):
        x, y = pos(i)
        tap = taps[i]
        dim = tap == ""
        o.append(f'<rect x="{x:.0f}" y="{y:.0f}" width="{K}" height="{K}" rx="9" fill="{"#f6f8fa" if dim else "#ffffff"}" stroke="#8c959f" stroke-width="1.3"/>')
        if dim:
            continue
        big = 24 if len(tap) <= 2 else (15 if len(tap) <= 6 else 12)
        o.append(t(x + K / 2, y + K / 2 + (8 if len(tap) <= 2 else 5), tap, big, weight="bold"))
        if holds[i]:
            o.append(t(x + K / 2, y + K - 7 if not corners else y + K / 2 + 22, holds[i], 11, fill=C["hold"], weight="bold"))
        if corners:
            for name, lab, cx, cy, anc in (("sym", SYM[i], x + 6, y + 15, "start"), ("num", NUM[i], x + K - 6, y + 15, "end"),
                                           ("nav", NAV[i], x + 6, y + K - 7, "start"), ("fun", FUN[i], x + K - 6, y + K - 7, "end")):
                if lab != ".":
                    o.append(t(cx, cy, lab, 11.5, fill=C[name], anchor=anc, weight="bold"))
    bx, by = pos(34)
    o.append(f'<circle cx="{bx + K + 62:.0f}" cy="{by + K / 2 - 6:.0f}" r="44" fill="#eaeef2" stroke="#8c959f" stroke-width="1.3"/>')
    o.append(t(bx + K + 62, by + K / 2 - 1, "ball", 14, fill="#57606a"))
    o.append("</g>")
    return o

def main():
    H = 150 + 3 * (BOARD_H + 70)
    o = [f'<svg xmlns="http://www.w3.org/2000/svg" viewBox="0 0 {W} {H}" width="{W}" height="{H}" font-family="Segoe UI, Arial, sans-serif">',
         f'<rect width="{W}" height="{H}" fill="#ffffff"/>',
         t(30, 44, "Charybdis Nano keymap (knaughtt)", 32, anchor="start", weight="bold")]
    x, ly = 30, 62
    for n, (name, col) in enumerate((("big letter = tap", "#1f2328"), ("red = hold", C["hold"]), ("top-left = Sym (hold Tab)", C["sym"]),
                      ("top-right = Num (hold Enter)", C["num"]), ("bottom-left = Nav (hold Q or ;)", C["nav"]),
                      ("bottom-right = Func (hold Esc or J)", C["fun"]))):
        if n == 3:
            x, ly = 30, 86
        o.append(f'<rect x="{x}" y="{ly}" width="14" height="14" rx="3" fill="{col}"/>')
        o.append(t(x + 20, ly + 12, name, 14, anchor="start"))
        x += 50 + len(name) * 7.6
    y = 170
    o += board(y, "1. Colemak-DH (default)", "Combos set in Argos: W+F = copy, R+S = paste.  Func layer: Wipe = clear stored settings, Boot = flash mode.", COLEMAK, HOLD, True)
    y += BOARD_H + 70
    o += board(y, "2. QWERTY fallback", "Toggle: hold Esc thumb, tap the left bottom inner key. Mods, thumbs and all four held layers are the same as above.", QWERTY, HOLD, False)
    y += BOARD_H + 70
    o += board(y, "3. Gaming (left half)  and  Mouse (right half)", "Gaming: double-tap / to enter and leave.   Mouse: turns on when the ball moves (or hold B); any other key returns to typing.", GAME_MOUSE, GM_HOLD, False)
    o.append("</svg>")
    out = os.path.join(os.path.dirname(os.path.abspath(__file__)), "..", "docs", "keymap.svg")
    os.makedirs(os.path.dirname(out), exist_ok=True)
    with open(out, "w", encoding="utf-8") as f:
        f.write("\n".join(o))
    print("wrote", os.path.normpath(out), "keys", len(COLEMAK), len(QWERTY), len(GAME_MOUSE), len(SYM), len(NUM), len(NAV), len(FUN), len(HOLD))

main()
