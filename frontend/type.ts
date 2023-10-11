import type { RouteLocationRaw } from 'vue-router';

export type MenuItem = MenuLinkItem | MenuButtonItem | MenuDropdownItem;

export interface BaseMenuItem {
  title: string;
}

export interface MenuLinkItem extends BaseMenuItem {
  type: 'link';
  to: RouteLocationRaw;
}

export interface MenuButtonItem extends BaseMenuItem {
  type: 'button';
}

export interface MenuDropdownItem extends BaseMenuItem {
  type: 'dropdown';
  children: (MenuLinkItem | MenuButtonItem)[];
}

export interface APIRequestBody<T> {
  code: number;
  body?: T;
}

export interface User {
  id: string;
  name: string;
  address: string;
  devices: string[];
}
