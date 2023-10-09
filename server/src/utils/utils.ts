export const getDate = (): `${string}/${string}/${string}` => {
  const now = new Date();

  return `${now.getFullYear()}/${now.getMonth() + 1}/${now.getDate()}`;
};

export const getHour = () => new Date().getHours();
