import type { RouteLocationRaw } from 'vue-router';

export declare type MenuItem = MenuLinkItem | MenuButtonItem | MenuDropdownItem;

export declare interface BaseMenuItem {
  title: string;
}

export declare interface MenuLinkItem extends BaseMenuItem {
  type: 'link';
  to: RouteLocationRaw;
}

export declare interface MenuButtonItem extends BaseMenuItem {
  type: 'button';
}

export declare interface MenuDropdownItem extends BaseMenuItem {
  type: 'dropdown';
  children: (MenuLinkItem | MenuButtonItem)[];
}
